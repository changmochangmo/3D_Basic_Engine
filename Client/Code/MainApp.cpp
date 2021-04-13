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
#include "BasicObject.h"
#include "Player.h"
#pragma endregion

CMainApp::CMainApp(void)
{
}

CMainApp::~CMainApp(void)
{
}

SP(CMainApp) CMainApp::Create(void)
{
	SP(CMainApp) pMainApp(new CMainApp, Engine::SmartDeleter<CMainApp>);

	return pMainApp;
}
void CMainApp::Awake(void)
{
	srand((_uint)time(NULL));

	Engine::CTextManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
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

	Engine::CTextManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CChangmoScene::Create());
	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CCameraManager::GetInstance()->Start();
	Engine::CShaderManager::GetInstance()->Start();
	
	Engine::CColliderManager::GetInstance()->Start((_int)EColliderID::NumOfColliderID);
}

void CMainApp::FixedUpdate(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CSceneManager::GetInstance()->FixedUpdate();
	Engine::CInputManager::GetInstance()->FixedUpdate();
	Engine::CGraphicsManager::GetInstance()->FixedUpdate();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::Update(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CSceneManager::GetInstance()->Update();
	Engine::CInputManager::GetInstance()->Update();
	Engine::CGraphicsManager::GetInstance()->Update();
	Engine::CCameraManager::GetInstance()->Update();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::LateUpdate(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->LateUpdate();
	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();
	Engine::CColliderManager::GetInstance()->LateUpdate();
	Engine::CCameraManager::GetInstance()->LateUpdate();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::PreRender(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->PreRender();
	Engine::CTextManager::GetInstance()->Render();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::Render(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->Render();
	Engine::CTextManager::GetInstance()->Render();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::PostRender(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->PostRender();
	Engine::CTextManager::GetInstance()->Render();

	_float time = Engine::GET_ELAPSED_TIME;
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
	Engine::CShaderManager::GetInstance()->DestroyInstance();
	Engine::CTextManager::GetInstance()->DestroyInstance();
}

void CMainApp::OnEnable(void)
{

}

void CMainApp::OnDisable(void)
{
}

void CMainApp::InitStaticPrototype(void)
{
	SP(Engine::CGameObject) spBasicObjectPrototype(CBasicObject::Create(true));
	Engine::ADD_PROTOTYPE(spBasicObjectPrototype);

	SP(Engine::CGameObject) spPlayerPrototype(CPlayer::Create(true));
	Engine::ADD_PROTOTYPE(spPlayerPrototype);
}
