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

void CScene::Awake(_int numOfLayers)
{
	m_isAwaked = true;

	InitLayers(numOfLayers);

	std::wstring className = GetCurClassName(this);
	CDataStore::GetInstance()->InitDataForScene(className);
	CMeshStore::GetInstance()->InitMeshForScene(className);
	CTextureStore::GetInstance()->InitTextureForScene(className);
}

void CScene::Start(void)
{
	
}

void CScene::FixedUpdate(void)
{
	for (auto& layer : m_vLayers)
	{
		if (layer->GetEnable())
			layer->FixedUpdate();
	}
}

void CScene::Update(void)
{
	for (auto& layer : m_vLayers)
	{
		if(layer->GetEnable())
			layer->Update();
	}
}

void CScene::LateUpdate(void)
{
	for (auto& layer : m_vLayers)
	{
		if (layer->GetEnable())
			layer->LateUpdate();
	}
}

void CScene::OnDestroy(void)
{
	for (auto& layer : m_vLayers)
		layer->Free();
}

void CScene::OnEnable(void)
{
}

void CScene::OnDisable(void)
{
}

SP(CGameObject) CScene::FindObjectByName(std::wstring name)
{
	for (auto& layer : m_vLayers)
	{
		for (auto& gameObject : layer->GetGameObjects())
		{
			if (gameObject->GetName() == name)
				return gameObject;
		}
	}
	return nullptr;
}

SP(CGameObject) CScene::FindObjectWithKey(std::wstring objectKey)
{
	for (auto& layer : m_vLayers)
	{
		for (auto& gameObject : layer->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				return gameObject;
		}
	}
	return nullptr;
}

_uint CScene::FindObjectsWithKey(std::wstring objectKey, std::vector<SP(CGameObject)>& gameObjects)
{
	for (auto& layer : m_vLayers)
	{
		for (auto& gameObject : layer->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				gameObjects.push_back(gameObject);
		}
	}
	return (_uint)gameObjects.size();
}

void CScene::InitLayers(_int numOfLayers)
{
	m_vLayers.reserve(numOfLayers);

	for (_int i = 0; i < numOfLayers; ++i)
		m_vLayers.emplace_back(CLayer::Create(i, this));

	return;
}