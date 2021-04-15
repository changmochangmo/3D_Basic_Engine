#include "EngineStdafx.h"
#include "Object.h"
#include "Layer.h"
#include "ObjectFactory.h"
USING(Engine)

CObject::CObject(void)
{
}

CObject::CObject(const CObject & other)
{
}

CObject::~CObject(void)
{
	OnDestroy();
}

void CObject::Awake(void)
{
	m_isAwaked = true;
	m_objectKey = GetCurClassName(this);
}

void CObject::Start(void)
{
	m_isStarted = true;
}

void CObject::FixedUpdate(void)
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

void CObject::Update(void)
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

void CObject::LateUpdate(void)
{
	for (auto& component : m_mComponents)
	{
		if (component.second->GetIsStarted() == false)
			continue;

		component.second->LateUpdate(component.second);
	}
}


void CObject::OnDestroy(void)
{
	for (auto& component : m_mComponents)
	{
		component.second->SetOwner(nullptr);
		component.second.reset();
	}

	m_mComponents.clear();
}

void CObject::OnEnable(void)
{
}


void CObject::OnDisable(void)
{
}

void CObject::InitClone(SP(CObject) spClone)
{
	spClone->SetIsClone(true);
	spClone->SetIsStatic(m_isStatic);

	spClone->SetIsAwaked(m_isAwaked);
	
	spClone->SetObjectKey(m_objectKey);
	spClone->SetDataID(m_dataID);
	spClone->SetLayerID(m_layerID);
	
	for (auto& component : m_mComponents)
	{
		spClone->CopyComponentToClone(component.second);
	}

	spClone->SetAddExtra(true);
}