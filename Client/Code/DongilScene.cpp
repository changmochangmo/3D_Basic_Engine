#include "stdafx.h"
#include "DongilScene.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "SceneManager.h"
#include "Layer.h"

#include "ColliderManager.h"

CDongilScene::CDongilScene()
{
}


CDongilScene::~CDongilScene()
{
}

SHARED(Engine::CScene) CDongilScene::Create(void)
{
	SHARED(CDongilScene) pCLogoScene(new CDongilScene, Engine::SmartDeleter<CDongilScene>);
	return pCLogoScene;
}

void CDongilScene::Awake(void)
{
	__super::Awake();

	InitLayers();
	InitPrototypes();
}

void CDongilScene::Start(void)
{
	__super::Start();

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	}
	
	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"Player", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(4, 15 ,3));
	}


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 3 && j == 7)
				continue;

			SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i, 0, 1.f * j));
		}
	}

	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i, 30, 1.f * j));
		}
	}*/

	/*for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(30, 10 + 1.f * i, 1.f * j));
		}
	}*/

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"BlueBlock", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(3.f, 0, 7.f));
		pObj->GetComponent<Engine::CTransformComponent>()->AddRotationZ(-45);
	}

	

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(10.0f, 10.0f, 1.0f));
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 0, 1));
		pObj->AddComponent<Engine::CUIComponent>()->SetTextureKey(L"MousePointUI");
	}
}

_uint CDongilScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return _uint();
}

_uint CDongilScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	return event;

}

_uint CDongilScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CDongilScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDongilScene::OnEnable(void)
{
}

void CDongilScene::OnDisable(void)
{
}

void CDongilScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"NormalBlock");
	AddLayer(L"EventBlock");
	AddLayer(L"Default");
}

void CDongilScene::InitPrototypes(void)
{

}

/*
	for(int i = 0; i < 10; i++)
	{
	for (int j = 0; j < 10; j++)
		{
			if (i == 3 && j == 7 || i == 7 && j == 6)
			continue;

			SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i, 0, 1.f * j));
		}
	}



	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RedBlock", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(3.f, -1, 7.f));
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RedBlock", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(7.f, -1, 6.f));
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"MoveBlock", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(3, 1, 3));
		pObj->GetComponent<CMoveBlockComponent>()->SetGoalPos(_float3(6, 1, 3));
	}
*/