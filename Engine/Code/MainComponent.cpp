#include "EngineStdafx.h"
#include "MainComponent.h"
#include "GameObject.h"

USING(Engine)
CMainComponent::CMainComponent() : CComponent(true)
{
}


CMainComponent::~CMainComponent()
{
}

void CMainComponent::Awake(void)
{
	__super::Awake();
}

void CMainComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_pOwner->SetMainComponent(spThis);
}

_uint CMainComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	__super::LateUpdate(spThis);
	return _uint();
}

_uint CMainComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CMainComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CMainComponent::OnDestroy(void)
{
}

void CMainComponent::OnEnable(void)
{
}

void CMainComponent::OnDisable(void)
{
}
