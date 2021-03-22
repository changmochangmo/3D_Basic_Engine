#include "stdafx.h"
#include "JiyongScene.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Layer.h"
#include "WndApp.h"
#include "LoadingScene.h"
#include "InputManager.h"

CJiyongScene::CJiyongScene()
{
}


CJiyongScene::~CJiyongScene()
{
}

SHARED(Engine::CScene) CJiyongScene::Create(void)
{
	SHARED(CJiyongScene) pScene(new CJiyongScene, Engine::SmartDeleter<CJiyongScene>);


	Engine::CSceneManager::GetInstance()->SetSceneName(L"JiyongScene");

	return pScene;
}

void CJiyongScene::Awake(void)
{
	__super::Awake();
	SetWindowText(Engine::GET_HANDLE, m_name.c_str());

	InitLayers();
	InitPrototypes();
}

void CJiyongScene::Start(void)
{
	__super::Start();
	SHARED(Engine::CGameObject) pObj = nullptr;

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"Player", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 10, 0));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i + 1.f, 0, 1.f * j + 1.f));
		}
	}

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"BlueBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(5, 0, 5));
	
	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(10.0f, 10.0f, 1.0f));
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 0, 1));
	pObj->AddComponent<Engine::CUIComponent>()->SetTextureKey(L"MousePointUI");

}

_uint CJiyongScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return _uint();
}

_uint CJiyongScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	return event;
}

_uint CJiyongScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CJiyongScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CJiyongScene::OnEnable(void)
{

}

void CJiyongScene::OnDisable(void)
{
}

void CJiyongScene::InitLayers(void)
{
	AddLayer(L"Default");
	AddLayer(L"Player");
	AddLayer(L"Camera");
	AddLayer(L"EventBlock");
	AddLayer(L"NormalBlock");
}

void CJiyongScene::InitPrototypes(void)
{
}