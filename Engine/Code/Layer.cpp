#include "EngineStdafx.h"
#include "Layer.h"
#include "Object.h"
#include "Scene.h"
#include "SceneManager.h"

USING(Engine)
CLayer::CLayer(void)
{
}

CLayer::~CLayer(void)
{
}

CLayer* CLayer::Create(_int layerID, CScene* pOwner)
{
	CLayer* pNewLayer = new CLayer;
	pNewLayer->SetLayerID(layerID);
	pNewLayer->SetOwner(pOwner);
	pNewLayer->Awake();

	return pNewLayer;
}

void CLayer::Free(void)
{
	OnDestroy();
	delete this;
}

void CLayer::Awake(void)
{
}

void CLayer::Start(void)
{
}

void CLayer::FixedUpdate(void)
{
	for (auto& gameObject : m_vGameObjects)
	{
		if (gameObject->GetDeleteThis())
			continue;

		if (gameObject->GetIsEnabled())
		{
			if (gameObject->GetIsStarted() == false)
				continue;

			gameObject->FixedUpdate();
		}
	}
}

void CLayer::Update(void)
{
	for (auto& it = m_vGameObjects.begin(); it != m_vGameObjects.end();)
	{
		if ((*it)->GetDeleteThis())
		{
			(*it).reset();			
			it = m_vGameObjects.erase(it);
		}
		else
		{
			if ((*it)->GetIsEnabled())
			{
				if ((*it)->GetIsStarted() == false)
					(*it)->Start();

				(*it)->Update();
			}
			++it;
		}
	}
}

void CLayer::LateUpdate(void)
{
	for (auto& gameObject : m_vGameObjects)
	{
		if (gameObject->GetDeleteThis()) 
			continue;

		if (gameObject->GetIsEnabled())
		{
			if (gameObject->GetIsStarted() == false)
				continue;

			gameObject->LateUpdate();
		}
	}
}

void CLayer::OnDestroy(void)
{
	m_vGameObjects.clear();
	m_vGameObjects.shrink_to_fit();
}

void CLayer::OnEnable(void)
{
}

void CLayer::OnDisable(void)
{
}

void CLayer::AddGameObject(SP(CObject) spGameObject)
{
	m_vGameObjects.emplace_back(spGameObject);
}
