#include "EngineStdafx.h"
#include "RayCollider.h"
#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"

USING(Engine)
CRayCollider::CRayCollider()
{
}


CRayCollider::~CRayCollider()
{
}

CRayCollider * CRayCollider::Create(_float3 offset, _float3 direction)
{
	CRayCollider* pRay = new CRayCollider();
	pRay->SetOffset(offset);
	pRay->SetDirection(direction);
	pRay->Awake();

	return pRay;
}

CCollider * CRayCollider::MakeClone(CCollisionC * pCC)
{
	CRayCollider* pRC = CRayCollider::Create(m_offset, m_direction);
	pRC->SetOwner(pCC);

	return pRC;
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

void CRayCollider::MakeBS(void)
{
	m_offsetBS = m_offset;
	m_radiusBS = FLT_MAX;
}
