#include "EngineStdafx.h"
#include "RayCollider.h"
#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"

USING(Engine)
CRayCollider::CRayCollider()
{
}


CRayCollider::~CRayCollider()
{
}

CRayCollider * CRayCollider::Create(_float3 offset, _float3 direction, _float length, ERayType rayType)
{
	CRayCollider* pRay = new CRayCollider;
	pRay->SetOffsetOrigin(offset);
	pRay->SetOffset(offset);
	pRay->SetDirectionOrigin(direction);
	pRay->SetDirection(direction);
	pRay->SetLength(length);
	pRay->SetRayType(rayType);
	pRay->Awake();

	return pRay;
}

CCollider * CRayCollider::MakeClone(CCollisionC * pCC)
{
	CRayCollider* pRayClone = new CRayCollider;
	pRayClone->SetOffsetOrigin(m_offsetOrigin);
	pRayClone->SetOffset(m_offsetOrigin);
	pRayClone->SetDirectionOrigin(m_directionOrigin);
	pRayClone->SetDirection(m_directionOrigin);
	pRayClone->SetLength(m_length);
	pRayClone->SetRayType(m_rayType);
	pRayClone->SetColliderType(m_colliderType);
	pRayClone->SetRadiusBS(m_radiusBS);

	pRayClone->SetOwner(pCC);

	return pRayClone;
}

void CRayCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_int)EColliderType::Ray;
}

void CRayCollider::OnDestroy(void)
{
}

void CRayCollider::OnEnable(void)
{
}

void CRayCollider::OnDisable(void)
{
}

void CRayCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
	if(m_pTarget == nullptr)
		D3DXVec3TransformNormal(&m_direction, &m_directionOrigin, &m_pOwner->GetTransform()->GetRotMatrix());
	else
	{
		m_direction = m_pTarget->GetTransform()->GetPosition() + _float3(0, 0.5f, 0) - (m_pOwner->GetTransform()->GetPosition() + m_offset);
		D3DXVec3Normalize(&m_direction, &m_direction);
	}
}

void CRayCollider::MakeBS(void)
{
	m_radiusBS = m_length;
}
