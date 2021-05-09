#include "EngineStdafx.h"
#include "PointCollider.h"


USING(Engine)
CPointCollider::CPointCollider()
{
}


CPointCollider::~CPointCollider()
{
}

CPointCollider * CPointCollider::Create(_float3 offset)
{
	CPointCollider* pPoint = new CPointCollider;
	pPoint->SetOffsetOrigin(offset);
	pPoint->Awake();

	return pPoint;
}

CCollider * CPointCollider::MakeClone(CCollisionC * pCC)
{
	CPointCollider* pPointClone = new CPointCollider;
	pPointClone->SetOffsetOrigin(m_offsetOrigin);
	pPointClone->SetRadiusBS(m_radiusBS);
	pPointClone->SetColliderType(m_colliderType);

	pPointClone->SetOwner(pCC);

	return pPointClone;
}

void CPointCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_uint)EColliderType::Point;
}

void CPointCollider::OnDestroy(void)
{
}

void CPointCollider::OnEnable(void)
{
}

void CPointCollider::OnDisable(void)
{
}

void CPointCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
}

void CPointCollider::MakeBS(void)
{
	m_radiusBS = 0.f;
}
