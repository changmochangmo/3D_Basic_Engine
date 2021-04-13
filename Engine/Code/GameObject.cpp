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

void CGameObject::FixedUpdate(void)
{
	for (auto& component : m_mComponents)
	{
		if (component.second->GetIsStarted() == false)
			continue;

		if (component.second->GetIsStarted() && component.second->GetIsAwaked())
		{
			component.second->FixedUpdate(component.second);
		}
	}
}

void CGameObject::Update(void)
{
	for (auto& component : m_mComponents)
	{
		if (m_mComponents.empty())
			continue;

		if (component.second->GetIsStarted() == false)
			component.second->Start(component.second);

		component.second->Update(component.second);
	}
}

void CGameObject::LateUpdate(void)
{
	for (auto& component : m_mComponents)
	{
		if (component.second->GetIsStarted() == false)
			continue;

		component.second->LateUpdate(component.second);
	}
}


void CGameObject::OnDestroy(void)
{
	for (auto& component : m_mComponents)
	{
		component.second->SetOwner(nullptr);
		component.second.reset();
	}

	m_mComponents.clear();
}

void CGameObject::OnEnable(void)
{
}


void CGameObject::OnDisable(void)
{
}

void CGameObject::InitClone(SP(CGameObject) spClone)
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