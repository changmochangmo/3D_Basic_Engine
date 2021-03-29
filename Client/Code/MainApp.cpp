#include "stdafx.h"
#include "MainApp.h"

#include "GraphicsManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ColliderManager.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "ShaderManager.h"
#include "FRC.h"
#include "TextManager.h"
#include "SoundManager.h"
#include "CameraManager.h"

#pragma region IncludeScenes
#include "ChangmoScene.h"
#pragma endregion

#pragma region Prototypes
#include "Player.h"
#pragma endregion

CMainApp::CMainApp(void)
{
}

CMainApp::~CMainApp(void)
{
}

SHARED(CMainApp) CMainApp::Create(void)
{
	SHARED(CMainApp) pMainApp(new CMainApp, Engine::SmartDeleter<CMainApp>);

	return pMainApp;
}
void CMainApp::Awake(void)
{
	srand((_uint)time(NULL));

	Engine::CInputManager::GetInstance()->Awake();
	Engine::CTextManager::GetInstance()->Awake();
	Engine::CSoundManager::GetInstance()->Awake();

	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CCameraManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CColliderManager::GetInstance()->Awake();

}

void CMainApp::Start(void)
{
	InitStaticPrototype();

	Engine::CInputManager::GetInstance()->Start();
	Engine::CTextManager::GetInstance()->Start();

	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CChangmoScene::Create());
	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CCameraManager::GetInstance()->Start();
	Engine::CShaderManager::GetInstance()->Start();
	
	Engine::CColliderManager::GetInstance()->Start((_int)EColliderID::NumOfColliderID);
}

_uint CMainApp::FixedUpdate(void)
{
	_uint event = NO_EVENT;

	Engine::TIME_MEASURE_START;
	if (event = Engine::CSceneManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CGraphicsManager::GetInstance()->FixedUpdate())	return event;
	_float time = Engine::GET_ELAPSED_TIME;

	return event;
}

_uint CMainApp::Update(void)
{
	_uint event = NO_EVENT;

	Engine::TIME_MEASURE_START;
	if (event = Engine::CSceneManager::GetInstance()->Update())		return event;
	if (event = Engine::CInputManager::GetInstance()->Update())		return event;
	if (event = Engine::CGraphicsManager::GetInstance()->Update())	return event;

	Engine::CCameraManager::GetInstance()->Update();
	_float time = Engine::GET_ELAPSED_TIME;
	return event;
}

_uint CMainApp::LateUpdate(void)
{
	_uint event = NO_EVENT;
	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->LateUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CSceneManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CColliderManager::GetInstance()->LateUpdate())	return event;

	Engine::CCameraManager::GetInstance()->LateUpdate();
	_float time = Engine::GET_ELAPSED_TIME;
	return event;
}

_uint CMainApp::PreRender(void)
{

	_uint event = NO_EVENT;
	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CTextManager::GetInstance()->Render())			return event;
	_float time = Engine::GET_ELAPSED_TIME;

	return event;
}

_uint CMainApp::Render(void)
{
	_uint event = NO_EVENT;
	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->Render())	return event;
	if (event = Engine::CTextManager::GetInstance()->Render())		return event;
	_float time = Engine::GET_ELAPSED_TIME;
	return event;
}

_uint CMainApp::PostRender(void)
{
	_uint event = NO_EVENT;
	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CTextManager::GetInstance()->Render())			return event;
	_float time = Engine::GET_ELAPSED_TIME;
	return event;
}

void CMainApp::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CObjectFactory::GetInstance()->DestroyInstance();
	Engine::CColliderManager::GetInstance()->DestroyInstance();
	Engine::CSoundManager::GetInstance()->DestroyInstance();
	Engine::CCameraManager::GetInstance()->DestroyInstance();
}

void CMainApp::OnEnable(void)
{

}

void CMainApp::OnDisable(void)
{
}

void CMainApp::InitStaticPrototype(void)
{
	SHARED(Engine::CGameObject) spPlayerPrototype(CPlayer::Create());
	Engine::CObjectFactory::GetInstance()->AddPrototype(spPlayerPrototype, true);
}
