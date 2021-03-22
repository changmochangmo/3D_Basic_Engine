#include "EngineStdafx.h"
#include "Component.h"
#include "GameObject.h"

USING(Engine)
CComponent::CComponent(_bool isMain) : m_isMain(isMain)
{
}
CComponent::~CComponent(void)
{
}

void CComponent::Awake(void)
{
	m_isAwaked = true;
	m_name = GetCurClassName(this);
}

void CComponent::Start(SHARED(CComponent) spThis)
{
	m_isStarted = true;
}

_uint CComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}


_uint CComponent::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

void CComponent::OnDestroy(void)
{
}

void CComponent::OnEnable(void)
{
	m_isEnabled = true;
}

void CComponent::OnDisable(void)
{
	m_isEnabled = false;
}