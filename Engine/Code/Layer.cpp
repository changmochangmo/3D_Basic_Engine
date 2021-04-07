#include "EngineStdafx.h"
#include "Layer.h"
#include "GameObject.h"
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

_uint CLayer::FixedUpdate(void)
{
	_uint event = NO_EVENT;	

	for (auto& pGameObject : m_vGameObjects)
	{
		if (pGameObject->GetIsStarted() == false)
			continue;

		pGameObject->FixedUpdate();
	}

	return event;
}

_uint CLayer::Update(void)
{
	_uint event = NO_EVENT;	
	

	for (auto& it = m_vGameObjects.begin(); it != m_vGameObjects.end();)
	{
		/*std::cout << (*it)->GetComponent<Engine::CTransformComponent>()->GetPosition().x << ", ";
		std::cout << (*it)->GetComponent<Engine::CTransformComponent>()->GetPosition().y << ", ";
		std::cout << (*it)->GetComponent<Engine::CTransformComponent>()->GetPosition().z << std::endl;*/

		if ((*it)->GetDeleteThis())
		{
			it->reset();			
			it = m_vGameObjects.erase(it);
		}
		else
		{
			if (m_vGameObjects.empty())
				return event;

			else if ((*it)->GetIsStarted() == false)
				(*it)->Start();


			(*it)->Update();
			++it;
		}
	}
	return event;
}

_uint CLayer::LateUpdate(void)
{
	_uint event = 0;

	for (auto& pGameObject : m_vGameObjects)
	{
		if (pGameObject->GetIsStarted() == false)
			continue;

		pGameObject->LateUpdate();
	}

	return event;
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

void CLayer::AddGameObject(SP(CGameObject) spGameObject)
{
	m_vGameObjects.emplace_back(spGameObject);
}
