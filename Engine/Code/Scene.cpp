#include "EngineStdafx.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "SceneManager.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"


USING(Engine)
CScene::CScene(void)
{
}
CScene::~CScene(void)
{
}

void CScene::Awake(void)
{
	if (!m_isAwaked)
	{
		m_isAwaked = true;
		m_name = GetCurClassName(this);
		CDataStore::GetInstance()->InitDataForScene(m_name);
		CMeshStore::GetInstance()->InitMeshForScene(m_name);
		CTextureStore::GetInstance()->InitTextureForScene(m_name);
	}
}

void CScene::Start(void)
{
	
}

_uint CScene::FixedUpdate(void)
{
	_uint event = 0;

	for (auto& layer : m_mLayers)
	{
		if (event = layer.second->FixedUpdate())
			return event;
	}
	return event;
}

_uint CScene::Update(void)
{
	_uint event = 0;	

	for (auto& layer : m_mLayers)
	{
		if (m_mLayers.empty())
			return event;

		if (event = layer.second->Update())
			return event;
	}
	return event;
}

_uint CScene::LateUpdate(void)
{
	_uint event = 0;

	for (auto& layer : m_mLayers)
	{
		if (event = layer.second->LateUpdate())
			return event;
	}
	return event;
}

void CScene::OnDestroy(void)
{
	m_mLayers.clear();
}

void CScene::OnEnable(void)
{
}

void CScene::OnDisable(void)
{
}

SHARED(CGameObject) CScene::FindObjectByName(std::wstring name)
{
	for (auto& layer : m_mLayers)
	{
		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetName() == name)
				return gameObject;
		}
	}
	return nullptr;
}

SHARED(CGameObject) CScene::FindObjectWithKey(std::wstring objectKey)
{
	for (auto& layer : m_mLayers)
	{
		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				return gameObject;
		}
	}
	return nullptr;
}

_uint CScene::FindObjectsWithKey(std::wstring objectKey, std::vector<SHARED(CGameObject)>& gameObjects)
{
	for (auto& layer : m_mLayers)
	{
		for (auto& gameObject : layer.second->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				gameObjects.push_back(gameObject);
		}
	}
	return gameObjects.size();
}

void CScene::AddLayer(std::wstring layerName)
{
	m_mLayers[layerName] = CLayer::Create(layerName);
}

