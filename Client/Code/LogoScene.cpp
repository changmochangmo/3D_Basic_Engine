#include "stdafx.h"
#include "LogoScene.h"
#include "WndApp.h"
#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "LoadingScene.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "Layer.h"
#include "SoundManager.h"

CLogoScene::CLogoScene(void)
{
}

CLogoScene::~CLogoScene(void)
{
}

SHARED(Engine::CScene) CLogoScene::Create(void)
{
	SHARED(CLogoScene) pCLogoScene(new CLogoScene, Engine::SmartDeleter<CLogoScene>);
	

	return pCLogoScene;
}


void CLogoScene::Awake(void)
{
	__super::Awake();
	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->PlayBGM(L"TitleSound.wav");
	InitLayers();
}

void CLogoScene::Start(void)
{
	__super::Start();

	m_name = GetCurClassName(this);
	SetWindowText(Engine::GET_HANDLE, m_name.c_str());

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(800.0f, 600.0f, 1.0f));
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 0, 1));
		pObj->AddComponent<Engine::CUIComponent>()->SetTextureKey(L"MainTitleUI");
	}

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();		
	}
}

_uint CLogoScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	_uint event = 0;
	if (event = __super::FixedUpdate())
		return event;


	return event;
}

_uint CLogoScene::Update(void)
{
	__super::Update();

	_uint event = 0;
	if (event = __super::Update())
		return event;

	if (Engine::IMKEY_DOWN(KEY_RETURN))
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CLoadingScene::Create(ESceneID::Stage1));
		return SCENE_CHANGE;
	}

	return event;
}

_uint CLogoScene::LateUpdate(void)
{
	__super::LateUpdate();

	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;


	return event;
}

void CLogoScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CLogoScene::OnEnable(void)
{
}

void CLogoScene::OnDisable(void)
{
}

void CLogoScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Default");
}

void CLogoScene::InitPrototypes(void)
{
}
