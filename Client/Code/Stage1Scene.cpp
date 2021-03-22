#include "stdafx.h"
#include "Stage1Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Layer.h"
#include "WndApp.h"
#include "LoadingScene.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "FontManager.h"

CStage1Scene::CStage1Scene() : m_Rot(0.f), m_EventCount(0), m_PreRotation(_float3(0.f, 0.f,0.f)), m_EventTimer(0.f), m_FowardVal(0.f)
{
	
}


CStage1Scene::~CStage1Scene()
{
	OnDestroy();
}

SHARED(Engine::CScene) CStage1Scene::Create(void)
{
	SHARED(CStage1Scene) pScene(new CStage1Scene, Engine::SmartDeleter<CStage1Scene>);

	Engine::CSceneManager::GetInstance()->SetSceneName(L"Stage1Scene");

	return pScene;
}

void CStage1Scene::Awake(void)
{
	__super::Awake();
	SetWindowText(Engine::GET_HANDLE, m_name.c_str());

	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->PlayBGM(L"Amb.wav");

	InitLayers();
	InitPrototypes();
}

void CStage1Scene::Start(void)
{
	__super::Start();
	SceneLoad();

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();	
  
	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"Player", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(2.f, 5.5f, -1.0f));
	m_pPlayer = pObj;
	
	
	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NextScenePoint", L"NextScenePoint", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(18.f, 14.f, -38.5f));
	pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(1.f, 1.f,1.f));

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(10.0f, 10.0f, 1.0f));
	pObj->AddComponent<Engine::CUIComponent>()->SetTextureKey(L"MousePointUI");


	// 1?¤í…Œ?´ì?
	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(2, 9, 0));
		pObj->GetComponent<Engine::CTransformComponent>()->AddRotationZ(45);
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(4,2,4) , FLOAT3_ZERO));
		pObj->GetComponent<Engine::CColliderComponent>()->SetColliderID(5);
		pObj->AddComponent<CElevator>()->Init(4, 4, 10);
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(2, 0, -13));
		pObj->GetComponent<Engine::CTransformComponent>()->AddRotationY(180);
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(4, 2, 1), _float3(0, 0, 5)));
		pObj->GetComponent<Engine::CColliderComponent>()->SetColliderID(5);
		pObj->AddComponent<CStairsComponent>()->Init(4, 1);
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1, 2, -27));
		pObj->GetComponent<Engine::CTransformComponent>()->AddRotationY(90);
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(4, 2, 4), FLOAT3_ZERO));
		pObj->GetComponent<Engine::CColliderComponent>()->SetColliderID(5);
		pObj->AddComponent<CDoor>();
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(18, 14, -39));
		pObj->GetComponent<Engine::CTransformComponent>()->AddRotationY(0);
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(_float3(4, 2, 4), FLOAT3_ZERO));
		pObj->GetComponent<Engine::CColliderComponent>()->SetColliderID(5);
		pObj->AddComponent<CDoor>();
	}

	
		 
}

_uint CStage1Scene::FixedUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::FixedUpdate())
		return event;
	
	if (m_pMainCamera->GetCameraEvent())
	{
		CameraEvent();
	}
	

	return event;
}

_uint CStage1Scene::Update(void)
{
	_uint event = NO_EVENT;
	if (event = __super::Update())
		return event;
	
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F2))
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CLoadingScene::Create(ESceneID::Stage2));

	}
	else if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F3))
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CLoadingScene::Create(ESceneID::Stage3));

	}

	return event;
}

_uint CStage1Scene::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::LateUpdate())
		return event;


	return event;
}

void CStage1Scene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CStage1Scene::OnEnable(void)
{

}

void CStage1Scene::OnDisable(void)
{
}

void CStage1Scene::InitLayers(void)
{
	AddLayer(L"Default");
	AddLayer(L"Player");
	AddLayer(L"Camera");
	AddLayer(L"EventBlock");
	AddLayer(L"NormalBlock");
	AddLayer(L"NextScenePoint");
}

void CStage1Scene::InitPrototypes(void)
{
}

HRESULT CStage1Scene::SceneLoad()
{
	SHARED(Engine::CGameObject) pObj = nullptr;

	auto& UnitInfo = Engine::CSceneManager::GetInstance()->GetUnitInfo().begin();

	for (auto& it = UnitInfo; it != Engine::CSceneManager::GetInstance()->GetUnitInfo().end();)
	{
		if (it->wsObjectKey == L"WhiteBlock")
		{
			pObj = Engine::ADD_CLONE(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(it->vPos);
			pObj->GetComponent<Engine::CTransformComponent>()->SetRotation(it->vRot);
		}
		else if (it->wsObjectKey == L"RedBlock")
		{
			pObj = Engine::ADD_CLONE(L"EventBlock", L"RedBlock", true);
			//pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(1.f, 3.f, 1.f));
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(it->vPos);
			pObj->GetComponent<Engine::CTransformComponent>()->SetRotation(it->vRot);
		}
		else if (it->wsObjectKey == L"BlueBlock")
		{
			pObj = Engine::ADD_CLONE(L"EventBlock", L"BlueBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(it->vPos);
			pObj->GetComponent<Engine::CTransformComponent>()->SetRotation(it->vRot);
		}
		else if (it->wsObjectKey == L"YellowBlock")
		{
			pObj = Engine::ADD_CLONE(L"EventBlock", L"YellowBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(1.f, 3.f, 1.f));
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(it->vPos);
			pObj->GetComponent<Engine::CTransformComponent>()->SetRotation(it->vRot);			

		}
		else if (it->wsObjectKey == L"GreenBlock")
		{
			pObj = Engine::ADD_CLONE(L"EventBlock", L"GreenBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(it->vPos);
			pObj->GetComponent<Engine::CTransformComponent>()->SetRotation(it->vRot);
		}
		
		++it;
	}

	return S_OK;
}

void CStage1Scene::CameraEvent()
{
	m_Rot = 30.f * GET_DT;
	
	m_pPlayer->GetComponent<Engine::CTransformComponent>()->AddPositionX(5.f * GET_DT);

	if (m_EventCount < 1)
	{
		m_EventTimer += GET_DT;
	}

	if (m_EventTimer < 3.f)
		return;

	switch (m_EventCount)
	{
	case 0:
		m_pMainCamera->GetTransform()->AddRotationX(-m_Rot);
		break;
	case 1:
		m_pMainCamera->GetTransform()->AddRotationX(m_Rot);
		m_pMainCamera->GetTransform()->AddRotationY(-m_Rot);
		break;
	case 2:
		m_pMainCamera->GetTransform()->AddRotationY(m_Rot);
		break;
	case 3:
		m_pMainCamera->GetTransform()->AddRotationY(-m_Rot);
		break;
	default:
		break;
	}

	if (m_pMainCamera->GetTransform()->GetRotation().x <= -45.f && m_EventCount < 1)
	{
		m_EventCount = 1;		
		m_PreRotation = m_pMainCamera->GetTransform()->GetRotation();
	}
	else if (m_pMainCamera->GetTransform()->GetRotation().x >= -4.f &&
		m_pMainCamera->GetTransform()->GetRotation().y <= m_PreRotation.y - 27.f &&
		m_EventCount >= 1)
	{
		m_EventCount = 2;
	}
	else if (m_pMainCamera->GetTransform()->GetRotation().x >=  -4.f &&
		m_pMainCamera->GetTransform()->GetRotation().y >= m_PreRotation.y + 25.f && m_EventCount >= 2)
	{
		m_EventCount = 3;
	}
	else if (m_pMainCamera->GetTransform()->GetRotation().x <= -2.f &&
		m_pMainCamera->GetTransform()->GetRotation().y <= m_PreRotation.y - 1.f && m_EventCount >= 3)
	{
		m_PreRotation = _float3(0.f, 0.f, 0.f);
		m_EventCount = -1;
		Engine::CSceneManager::GetInstance()->SceneChange(CLoadingScene::Create(ESceneID::Stage2));
		m_pMainCamera->SetCameraEvent(false);
	}	
}
