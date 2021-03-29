#include "EngineStdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectFactory.h"
#include "MeshStore.h"
#include "TextureStore.h"
#include "DataStore.h"
#include "GameObject.h"
#include "WndApp.h"
#include "FRC.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSceneManager)
void CSceneManager::Awake(void)
{
	__super::Awake();
}

void CSceneManager::Start(void)
{
}

_uint CSceneManager::FixedUpdate(void)
{
	_uint event = NO_EVENT;
	if (m_pCurScene != nullptr && m_pCurScene->GetEnable())
	{
		if (event = m_pCurScene->FixedUpdate())
			return event;
	}
	return event;
}

_uint CSceneManager::Update(void)
{
	_uint event = NO_EVENT;
	if (m_pCurScene != nullptr && m_pCurScene->GetEnable())
	{
		if (event = m_pCurScene->Update())
			return event;
	}
	return event;
}

_uint CSceneManager::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (m_pCurScene != nullptr && m_pCurScene->GetEnable())
	{
		if (event = m_pCurScene->LateUpdate())
			return event;
	}
	return event;
}



void CSceneManager::OnDestroy(void)
{
	while (m_sScene.size() != 0)
	{
		m_sScene.top()->Free();
		m_sScene.pop();
	}
}

void CSceneManager::OnEnable(void)
{
}

void CSceneManager::OnDisable(void)
{
}


void CSceneManager::SceneChange(CScene* pScene, _bool deleteCurScene/* = true */)
{
	if (m_pCurScene && deleteCurScene)
	{
		m_sScene.top()->Free();
		CObjectFactory::GetInstance()->ClearCurPrototype();
		CMeshStore::GetInstance()->ClearCurResource();
		CTextureStore::GetInstance()->ClearCurResource();
		CDataStore::GetInstance()->ClearCurResource();
		m_sScene.pop();
	}
	else if (m_pCurScene)
	{
		m_pCurScene->SetEnable(false);
		m_pPrevScene = m_pCurScene;
	}

	m_sScene.push(pScene);
	m_pCurScene = pScene;
	m_pCurScene->Start();
}

void CSceneManager::OrganizeScene(_bool deleteCurScene)
{
	
}