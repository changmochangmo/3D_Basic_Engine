#include "stdafx.h"
#include "MainMenuScene.h"
#include "WndApp.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "LogoScene.h"

CMainMenuScene::CMainMenuScene(void)
{
}

CMainMenuScene::~CMainMenuScene(void)
{
}

SHARED(Engine::CScene) CMainMenuScene::Create(void)
{
	SHARED(CMainMenuScene) pCLogoScene(new CMainMenuScene, Engine::SmartDeleter<CMainMenuScene>);

	return pCLogoScene;
}


void CMainMenuScene::Awake(void)
{
}

void CMainMenuScene::OnEnable(void)
{
}

void CMainMenuScene::Start(void)
{
	m_name = GetCurClassName(this);
	SetWindowText(Engine::GET_HANDLE, m_name.c_str());
}

_uint CMainMenuScene::FixedUpdate(void)
{
	_uint event = 0;
	if (event = __super::FixedUpdate())
		return event;


	return event;
}

_uint CMainMenuScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CLogoScene::Create());
		return SCENE_CHANGE;
	}

	return event;
}

_uint CMainMenuScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;


	return event;
}

void CMainMenuScene::OnDisable(void)
{
}

void CMainMenuScene::InitLayers(void)
{
}

void CMainMenuScene::InitPrototypes(void)
{
}

void CMainMenuScene::OnDestroy(void)
{
	__super::OnDestroy();
}
