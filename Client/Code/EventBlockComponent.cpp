#include "stdafx.h"
#include "EventBlockComponent.h"
#include "GameObject.h"

CEventBlockComponent::CEventBlockComponent()
{
}


CEventBlockComponent::~CEventBlockComponent()
{
}

void CEventBlockComponent::Awake(void)
{
	__super::Awake();
	m_pOwner->SetLayerKey(L"EventBlock");
}

void CEventBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	if (auto& pCC = m_pOwner->GetComponent<Engine::CColliderComponent>())
		pCC->SetColliderID((_int)EColliderID::EventBlock);
}

_uint CEventBlockComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CEventBlockComponent::Update(SHARED(Engine::CComponent) spThis)
{

	return _uint();
}

_uint CEventBlockComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CEventBlockComponent::OnDestroy(void)
{
}

void CEventBlockComponent::OnEnable(void)
{
}

void CEventBlockComponent::OnDisable(void)
{
}

