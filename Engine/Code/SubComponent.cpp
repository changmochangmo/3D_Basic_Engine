#include "EngineStdafx.h"
#include "SubComponent.h"


USING(Engine)
CSubComponent::CSubComponent() : CComponent(false)
{
}


CSubComponent::~CSubComponent()
{
}

void CSubComponent::Awake(void)
{
	__super::Awake();

}

void CSubComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CSubComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CSubComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CSubComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CSubComponent::OnDestroy(void)
{
}

void CSubComponent::OnEnable(void)
{
}

void CSubComponent::OnDisable(void)
{
}
