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
	OnDestroy();
}

SHARED(CLayer) CLayer::Create(std::wstring name)
{
	SHARED(CLayer) pLayer(new CLayer, SmartDeleter<CLayer>);
	pLayer->SetName(name);
	pLayer->Awake();

	return pLayer;
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

		if (event = pGameObject->FixedUpdate())
			return event;
	}

	return event;
}

_uint CLayer::Update(void)
{
	_uint event = NO_EVENT;	

	if (m_name == L"EventBlock")
	{
		int i = 0;
	}
	

	for (auto& it = m_vGameObjects.begin(); it != m_vGameObjects.end();)
	{
		/*std::cout << (*it)->GetComponent<Engine::CTransformComponent>()->GetPosition().x << ", ";
		std::cout << (*it)->GetComponent<Engine::CTransformComponent>()->GetPosition().y << ", ";
		std::cout << (*it)->GetComponent<Engine::CTransformComponent>()->GetPosition().z << std::endl;*/

		if ((*it)->GetIsNeedToBeDeleted())
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


			else if (event = (*it)->Update())
				return event;

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

		if (event = pGameObject->LateUpdate())
			return event;
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
