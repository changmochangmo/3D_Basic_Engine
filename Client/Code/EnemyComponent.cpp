#include "stdafx.h"
#include "EnemyComponent.h"
#include "GameObject.h"


CEnemyComponent::CEnemyComponent()
{
}


CEnemyComponent::~CEnemyComponent()
{
}

SHARED(Engine::CComponent) CEnemyComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CEnemyComponent) pClone(new CEnemyComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CEnemyComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
	m_pOwner->SetLayerKey(L"Enemy");
	m_pOwner->SetObjectKey(L"Enemy");
}

void CEnemyComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CEnemyComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CEnemyComponent::Update(SHARED(Engine::CComponent) spThis)
{
	_float3 dir = m_pPlayerTransform->GetPosition() - m_pOwner->GetComponent<Engine::CTransformComponent>()->GetPosition();

	D3DXVec3Normalize(&dir, &dir);

	_float cosTheta = dir.y;

	_float angle = acosf(cosTheta);

	
	m_pOwner->GetComponent<Engine::CTransformComponent>()->SetRotationZ(angle);
	

	m_pOwner->GetComponent<Engine::CTransformComponent>()->AddPosition(dir * 0.016);

	return _uint();
}

_uint CEnemyComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CEnemyComponent::OnDestroy(void)
{
}

void CEnemyComponent::OnEnable(void)
{
}

void CEnemyComponent::OnDisable(void)
{
}
