#include "stdafx.h"
#include "NormalBlockComponent.h"
#include "GameObject.h"

CNormalBlockComponent::CNormalBlockComponent()
{
}


CNormalBlockComponent::~CNormalBlockComponent()
{
}

void CNormalBlockComponent::Awake(void)
{
	__super::Awake();
	m_pOwner->SetLayerKey(L"NormalBlock");
}

void CNormalBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	if (auto& pCC = m_pOwner->GetComponent<Engine::CColliderComponent>())
		pCC->SetColliderID((_int)EColliderID::NormalBlock);
}

_uint CNormalBlockComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CNormalBlockComponent::Update(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CNormalBlockComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CNormalBlockComponent::OnDestroy(void)
{
}

void CNormalBlockComponent::OnEnable(void)
{
}

void CNormalBlockComponent::OnDisable(void)
{
}
