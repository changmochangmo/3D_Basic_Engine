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

CRayCollider * CRayCollider::Create(_float3 offset, _float3 direction, _float length)
{
	CRayCollider* pRay = new CRayCollider;
	pRay->SetOffset(offset);
	pRay->SetDirection(direction);
	pRay->SetLength(length);
	pRay->Awake();

	return pRay;
}

CCollider * CRayCollider::MakeClone(CCollisionC * pCC)
{
	CRayCollider* pRayClone = new CRayCollider;
	pRayClone->SetOffset(m_offset);
	pRayClone->SetDirection(m_direction);
	pRayClone->SetLength(m_length);

	pRayClone->SetColliderType(m_colliderType);

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
}

void CRayCollider::MakeBS(void)
{
	m_radiusBS = 0;
}
