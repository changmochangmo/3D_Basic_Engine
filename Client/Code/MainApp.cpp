#include "stdafx.h"
#include "MainApp.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "TextManager.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "FRC.h"


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

SP(CMainApp) CMainApp::Create(void)
{
	SP(CMainApp) pMainApp(new CMainApp, Engine::SmartDeleter<CMainApp>);

	return pMainApp;
}
void CMainApp::Awake(void)
{
	srand((_uint)time(NULL));

	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSoundManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CCameraManager::GetInstance()->Awake();
	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CCollisionManager::GetInstance()->Awake();
}

void CMainApp::Start(void)
{
	InitStaticPrototype();

	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CChangmoScene::Create());
	Engine::CCameraManager::GetInstance()->Start();
	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CShaderManager::GetInstance()->Start();
	
	Engine::CCollisionManager::GetInstance()->Start((_int)EColliderID::NumOfColliderID);
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

	Engine::CInputManager::GetInstance()->Update();
	Engine::CSceneManager::GetInstance()->Update();
	
	Engine::CCameraManager::GetInstance()->Update();
	Engine::CCollisionManager::GetInstance()->Update();
	Engine::CGraphicsManager::GetInstance()->Update();
	

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::LateUpdate(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();
	
	Engine::CCameraManager::GetInstance()->LateUpdate();
	Engine::CCollisionManager::GetInstance()->LateUpdate();
	Engine::CGraphicsManager::GetInstance()->LateUpdate();	

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::PreRender(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->PreRender();
	Engine::CTextManager::GetInstance()->PreRender();

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
	Engine::CTextManager::GetInstance()->PostRender();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CObjectFactory::GetInstance()->DestroyInstance();
	Engine::CCollisionManager::GetInstance()->DestroyInstance();
	Engine::CSoundManager::GetInstance()->DestroyInstance();
	Engine::CCameraManager::GetInstance()->DestroyInstance();
	Engine::CShaderManager::GetInstance()->DestroyInstance();
}

void CMainApp::OnEnable(void)
{

}

void CMainApp::OnDisable(void)
{
}

void CMainApp::InitStaticPrototype(void)
{
	SP(Engine::CObject) spPlayerPrototype(CPlayer::Create(true));
	Engine::ADD_PROTOTYPE(spPlayerPrototype);
}
