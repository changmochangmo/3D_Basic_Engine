#include "stdafx.h"
#include "Stage2Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Layer.h"
#include "WndApp.h"
#include "LoadingScene.h"
#include "InputManager.h"
#include "SoundManager.h"

CStage2Scene::CStage2Scene()
{
}


CStage2Scene::~CStage2Scene()
{
	OnDestroy();
}

SHARED(Engine::CScene) CStage2Scene::Create(void)
{
	SHARED(CStage2Scene) pScene(new CStage2Scene, Engine::SmartDeleter<CStage2Scene>);

	Engine::CSceneManager::GetInstance()->SetSceneName(L"Stage2Scene");

	return pScene;
}

void CStage2Scene::Awake(void)
{
	__super::Awake();
	SetWindowText(Engine::GET_HANDLE, m_name.c_str());

	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->PlayBGM(L"Amb.wav");

	InitLayers();
	InitPrototypes();
}

void CStage2Scene::Start(void)
{
	__super::Start();
	SceneLoad();

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();	

	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"Player", true);

	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(3.f, 3.f, 3.f));


	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NextScenePoint", L"NextScenePoint", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(11.f, 30.f, 16.f));
	pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(1.f, 1.f, 1.f));


	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(10.0f, 10.0f, 1.0f));
	pObj->AddComponent<Engine::CUIComponent>()->SetTextureKey(L"MousePointUI");
}

_uint CStage2Scene::FixedUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::FixedUpdate())
		return event;

	return event;
}

_uint CStage2Scene::Update(void)
{
	_uint event = NO_EVENT;
	if (event = __super::Update())
		return event;

	if(m_pMainCamera->GetCameraEvent())
		Engine::CSceneManager::GetInstance()->SceneChange(CLoadingScene::Create(ESceneID::Stage3));


	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F1))
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CLoadingScene::Create(ESceneID::Stage1));
	}	
	else if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F3))
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CLoadingScene::Create(ESceneID::Stage3));
	}
	else if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F2))
	{
		std::cout << m_pMainCamera->GetTransform()->GetPosition().x << ", ";
		std::cout << m_pMainCamera->GetTransform()->GetPosition().y << ", ";
		std::cout << m_pMainCamera->GetTransform()->GetPosition().z << std::endl;
	}

	return event;
}

_uint CStage2Scene::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::LateUpdate())
		return event;


	return event;
}

void CStage2Scene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CStage2Scene::OnEnable(void)
{

}

void CStage2Scene::OnDisable(void)
{
}

void CStage2Scene::InitLayers(void)
{
	AddLayer(L"Default");
	AddLayer(L"Player");
	AddLayer(L"Camera");
	AddLayer(L"EventBlock");
	AddLayer(L"NormalBlock");
	AddLayer(L"NextScenePoint");

}

void CStage2Scene::InitPrototypes(void)
{
}

HRESULT CStage2Scene::SceneLoad()
{
	SHARED(Engine::CGameObject) pObj = nullptr;

	// ¿©±â¼­ ºÎÅÍ ¼öÁ¤
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