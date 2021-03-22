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
#include "FontManager.h"
#include "UIManager.h"
#include "SoundManager.h"

#pragma region IncludeScenes
#include "LogoScene.h"
#include "LoadingScene.h"
#include "ChangmoScene.h"
#include "DongilScene.h"
#include "WooHyeongScene.h"
#include "JiyongScene.h"
#include "EventScene.h"
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
	ClientSetting();
	srand((unsigned)time(NULL));

	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CUIManager::GetInstance()->Awake();
	Engine::CFontManager::GetInstance()->Awake();
	Engine::CColliderManager::GetInstance()->Awake();
	Engine::CSoundManager::GetInstance()->Awake();

}

void CMainApp::Start(void)
{
	InitStaticPrototype();
	BlockPrototype();

	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CChangmoScene::Create());
	Engine::CShaderManager::GetInstance()->Start();
	Engine::CUIManager::GetInstance()->Start();
	Engine::CFontManager::GetInstance()->Start();
	Engine::CColliderManager::GetInstance()->Start((_int)EColliderID::NumOfColliderID);
}

_uint CMainApp::FixedUpdate(void)
{
	_uint event = NO_EVENT;

	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CSceneManager::GetInstance()->FixedUpdate())	return event;
	_float time = Engine::GET_ELAPSED_TIME;

	return event;
}

_uint CMainApp::Update(void)
{
	_uint event = NO_EVENT;

	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->Update())	return event;
	if (event = Engine::CInputManager::GetInstance()->Update())		return event;
	if (event = Engine::CSceneManager::GetInstance()->Update())		return event;
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
	_float time = Engine::GET_ELAPSED_TIME;
	return event;
}

_uint CMainApp::PreRender(void)
{

	_uint event = NO_EVENT;
	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CFontManager::GetInstance()->Render())			return event;
	_float time = Engine::GET_ELAPSED_TIME;

	return event;
}

_uint CMainApp::Render(void)
{
	_uint event = NO_EVENT;
	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->Render())	return event;
	if (event = Engine::CUIManager::GetInstance()->Render())		return event;
	if (event = Engine::CFontManager::GetInstance()->Render())		return event;
	_float time = Engine::GET_ELAPSED_TIME;
	return event;
}

_uint CMainApp::PostRender(void)
{
	_uint event = NO_EVENT;
	Engine::TIME_MEASURE_START;
	if (event = Engine::CGraphicsManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CUIManager::GetInstance()->PostRender())		return event;
	if (event = Engine::CFontManager::GetInstance()->Render())			return event;
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
}

void CMainApp::OnEnable(void)
{

}

void CMainApp::OnDisable(void)
{
}

void CMainApp::ClientSetting()
{
	ShowCursor(false);
}

void CMainApp::InitStaticPrototype(void)
{
	SHARED(Engine::CGameObject) pDefault = Engine::CGameObject::Create(L"Default", L"Default", true);
	pDefault->AddComponent<Engine::CTransformComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pDefault);

	SHARED(Engine::CGameObject) pNextScenePoint = Engine::CGameObject::Create(L"NextScenePoint", L"NextScenePoint", true);
	pNextScenePoint->AddComponent<CNextPointComponent>();
	pNextScenePoint->AddComponent<Engine::CMeshComponent>();
	pNextScenePoint->AddComponent<Engine::CTextureComponent>();
	pNextScenePoint->AddComponent<Engine::CTransformComponent>();
	pNextScenePoint->AddComponent<Engine::CGraphicsComponent>();
	pNextScenePoint->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(1.f, 1.f, 1.f), FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pNextScenePoint);

	SHARED(Engine::CGameObject) pCamera = Engine::CGameObject::Create(L"Camera", L"Camera", true);
	pCamera->AddComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 2, 0));
	pCamera->AddComponent<Engine::CCameraComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pCamera);

	SHARED(Engine::CGameObject) pPlayer = Engine::CGameObject::Create(L"Player", L"Player", true);
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"Cube");
	pPlayer->AddComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 1, 0));
	pPlayer->AddComponent<CPlayerComponent>();	
	pPlayer->AddComponent<Engine::CTextureComponent>()->SetTextureKey(L"BlueBlock");
	pPlayer->AddComponent<Engine::CGraphicsComponent>();
	//pPlayer->AddComponent<Engine::CRigidBodyComponent>()->SetMass(50.0f);
	//pPlayer->GetComponent<Engine::CRigidBodyComponent>()->SetBounciness(0.0f);
	//pPlayer->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(0.5f, 2.0f, 0.5f), FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pPlayer);

	SHARED(Engine::CGameObject) pEnemy = Engine::CGameObject::Create(L"Enemy", L"Enemy", true);
	pEnemy->AddComponent<Engine::CTransformComponent>();
	pEnemy->AddComponent<CEnemyComponent>();
	pEnemy->AddComponent<Engine::CTextureComponent>()->SetTextureKey(L"BlueBlock");
	pEnemy->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"Cube");
	pEnemy->AddComponent<Engine::CGraphicsComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pEnemy);
}

void CMainApp::BlockPrototype()
{
	SHARED(Engine::CGameObject) pWhiteBlock = Engine::CGameObject::Create(L"NormalBlock", L"WhiteBlock", true);
	pWhiteBlock->AddComponent<CWhiteBlockComponent>();
	pWhiteBlock->AddComponent<Engine::CMeshComponent>();
	pWhiteBlock->AddComponent<Engine::CTextureComponent>()->SetColor(D3DXVECTOR4(1.f, 1.f, 1.f, 0.5f));
	pWhiteBlock->AddComponent<Engine::CTransformComponent>();
	pWhiteBlock->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(FLOAT3_ONE, FLOAT3_ZERO));
	pWhiteBlock->AddComponent<Engine::CGraphicsComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pWhiteBlock);

	SHARED(Engine::CGameObject) pBlueBlock = Engine::CGameObject::Create(L"EventBlock", L"BlueBlock", true);
	pBlueBlock->AddComponent<CBlueBlockComponent>();
	pBlueBlock->AddComponent<Engine::CMeshComponent>();
	pBlueBlock->AddComponent<Engine::CTextureComponent>();
	pBlueBlock->AddComponent<Engine::CTransformComponent>();
	pBlueBlock->AddComponent<Engine::CGraphicsComponent>();
	pBlueBlock->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(FLOAT3_ONE, FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pBlueBlock);

	SHARED(Engine::CGameObject) pRedBlock = Engine::CGameObject::Create(L"EventBlock", L"RedBlock", true);
	pRedBlock->AddComponent<CRedBlockComponent>();
	pRedBlock->AddComponent<Engine::CMeshComponent>();
	pRedBlock->AddComponent<Engine::CTextureComponent>();
	pRedBlock->AddComponent<Engine::CTransformComponent>();
	pRedBlock->AddComponent<Engine::CGraphicsComponent>();
	pRedBlock->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(1.f, 3.f, 1.f), FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pRedBlock);

	SHARED(Engine::CGameObject) pYellowBlock = Engine::CGameObject::Create(L"EventBlock", L"YellowBlock", true);
	pYellowBlock->AddComponent<CYellowBlockComponent>();
	pYellowBlock->AddComponent<Engine::CMeshComponent>();
	pYellowBlock->AddComponent<Engine::CTextureComponent>();
	pYellowBlock->AddComponent<Engine::CTransformComponent>();
	pYellowBlock->AddComponent<Engine::CGraphicsComponent>();
	pYellowBlock->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(1.f, 3.f, 1.f), FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pYellowBlock);

	SHARED(Engine::CGameObject) pGreenBlock = Engine::CGameObject::Create(L"EventBlock", L"GreenBlock", true);
	pGreenBlock->AddComponent<CGreenBlockComponent>();
	pGreenBlock->AddComponent<Engine::CMeshComponent>();
	pGreenBlock->AddComponent<Engine::CTextureComponent>();
	pGreenBlock->AddComponent<Engine::CTransformComponent>();
	pGreenBlock->AddComponent<Engine::CGraphicsComponent>();
	pGreenBlock->AddComponent<Engine::CRigidBodyComponent>()->SetMass(5.0f);
	pGreenBlock->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(0.8f, 0.8f, 0.8f), FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pGreenBlock);

	SHARED(Engine::CGameObject) pRhythmBlock = Engine::CGameObject::Create(L"EventBlock", L"RhythmBlock", true);
	pRhythmBlock->AddComponent<CRhythmBlockComponent>();
	pRhythmBlock->AddComponent<Engine::CMeshComponent>();
	pRhythmBlock->AddComponent<Engine::CTextureComponent>();
	pRhythmBlock->AddComponent<Engine::CTransformComponent>();
	pRhythmBlock->AddComponent<Engine::CGraphicsComponent>();
	pRhythmBlock->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(0.3f, 1.f, 0.3f), FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pRhythmBlock);

  
	SHARED(Engine::CGameObject) pMoveBlock = Engine::CGameObject::Create(L"EventBlock", L"MoveBlock", true);
	pMoveBlock->AddComponent<CMoveBlockComponent>();
	pMoveBlock->AddComponent<Engine::CMeshComponent>();
	pMoveBlock->AddComponent<Engine::CTextureComponent>();
	pMoveBlock->AddComponent<Engine::CTransformComponent>();
	pMoveBlock->AddComponent<Engine::CGraphicsComponent>();
	pMoveBlock->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(1.f, 1.f, 1.f), FLOAT3_ZERO));
	Engine::CObjectFactory::GetInstance()->AddPrototype(pMoveBlock);

	SHARED(Engine::CGameObject) pUITest = Engine::CGameObject::Create(L"UI", L"Test", true);
	pUITest->AddComponent<Engine::CBitmapComponent>();
	pUITest->AddComponent<Engine::CTransformComponent>();
	pUITest->AddComponent<Engine::CTextureComponent>();
	pUITest->AddComponent<Engine::CGraphicsComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pUITest);

}
