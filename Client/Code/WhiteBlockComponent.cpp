#include "stdafx.h"
#include "WhiteBlockComponent.h"
#include "GameObject.h"

CWhiteBlockComponent::CWhiteBlockComponent(void)
{

}

SHARED(Engine::CComponent) CWhiteBlockComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CWhiteBlockComponent) pClone(new CWhiteBlockComponent);
	pClone->SetOwner(pObject);
	pClone->Awake();

	return pClone;

}

void CWhiteBlockComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
	m_pOwner->SetObjectKey(L"WhiteBlock");
}

void CWhiteBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CWhiteBlockComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CWhiteBlockComponent::Update(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CWhiteBlockComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CWhiteBlockComponent::OnDestroy(void)
{
}

void CWhiteBlockComponent::OnEnable(void)
{
}

void CWhiteBlockComponent::OnDisable(void)
{
}
