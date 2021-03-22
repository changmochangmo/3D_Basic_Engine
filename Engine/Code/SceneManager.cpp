#include "EngineStdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectFactory.h"
#include "MeshStore.h"
#include "TextureStore.h"
#include "DataStore.h"
#include "GameObject.h"
#include "WndApp.h"

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
	TIME_MEASURE_START;
	if (m_pCurScene != nullptr && m_pCurScene->GetEnable())
	{
		if (event = m_pCurScene->Update())
			return event;
	}
	_float time = GET_ELAPSED_TIME;
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
		m_sScene.pop();
	
	m_vUnitInfo.clear();
}

void CSceneManager::OnEnable(void)
{
}

void CSceneManager::OnDisable(void)
{
}


void CSceneManager::SceneChange(SHARED(CScene) pScene, bool needToBeCleaned/* = true */)
{
	m_needToBeCleaned = needToBeCleaned;
	m_pNextScene = pScene;

	OrganizeScene();
}

void CSceneManager::OrganizeScene(void)
{
	if (m_needToBeCleaned)
	{
		while (m_sScene.size() != 0)
		{
			m_sScene.top().reset();
			CObjectFactory::GetInstance()->ClearCurPrototype();
			CMeshStore::GetInstance()->ClearCurResource();
			CTextureStore::GetInstance()->ClearCurResource();
			CDataStore::GetInstance()->ClearCurResource();
			m_sScene.pop();
		}
		m_needToBeCleaned = false;
	}
	else if (m_pCurScene)
		m_pCurScene->SetEnable(false);

	m_sScene.push(m_pNextScene);
	m_pCurScene = m_pNextScene;
	m_pCurScene->Awake();
	m_pCurScene->Start();

	m_pNextScene.reset();
}