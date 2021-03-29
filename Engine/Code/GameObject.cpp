#include "EngineStdafx.h"
#include "GameObject.h"
#include "Layer.h"
#include "ObjectFactory.h"
USING(Engine)

CGameObject::CGameObject(void)
{
}

CGameObject::CGameObject(const CGameObject & other)
{
}

CGameObject::~CGameObject(void)
{
	OnDestroy();
}




void CGameObject::Awake(void)
{
	m_isAwaked = true;
	m_objectKey = GetCurClassName(this);
}

void CGameObject::Start(void)
{
	m_isStarted = true;
}

_uint CGameObject::FixedUpdate(void)
{

	_uint event = NO_EVENT;
	for (auto& component : m_mComponents)
	{
		if (component.second->GetIsStarted() == false)
			continue;

		if (component.second->GetIsStarted() && component.second->GetIsAwaked())
		{
			if (event = component.second->FixedUpdate(component.second))
				return event;
		}
	}

	return event;
}

_uint CGameObject::Update(void)
{
	_uint event = NO_EVENT;

	for (auto& component : m_mComponents)
	{
		if (m_mComponents.empty())
			continue;

		if (component.second->GetIsStarted() == false)
			component.second->Start(component.second);

		if (event = component.second->Update(component.second))
			return event;
	}

	return event;
}

_uint CGameObject::LateUpdate(void)
{
	_uint event = NO_EVENT;

	for (auto& component : m_mComponents)
	{
		if (component.second->GetIsStarted() == false)
			continue;

		if (event = component.second->LateUpdate(component.second))
			return event;
	}
	return event;
}


void CGameObject::OnDestroy(void)
{
	for (auto& component : m_mComponents)
		component.second->SetOwner(nullptr);

	m_mComponents.clear();
}

void CGameObject::OnEnable(void)
{
}


void CGameObject::OnDisable(void)
{
}

void CGameObject::InitClone(SHARED(CGameObject) spClone)
{
	spClone->SetIsClone(true);
	spClone->SetIsStatic(m_isStatic);

	spClone->SetIsAwaked(m_isAwaked);
	
	spClone->SetObjectKey(m_objectKey);
	spClone->SetDataID(m_dataID);
	spClone->SetLayerID(m_layerID);
	
	for (auto& component : m_mComponents)
	{
		spClone->AddComponentToClone(component.second);
	}
}