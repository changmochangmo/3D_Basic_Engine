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
	pPoint->SetOffset(offset);
	pPoint->Awake();

	return pPoint;
}

CCollider * CPointCollider::MakeClone(CColliderComponent * pCC)
{
	CPointCollider* pPC = CPointCollider::Create(m_offset);
	pPC->SetOwner(pCC);

	return pPC;
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

void CPointCollider::MakeBS(void)
{
	m_offsetBS = m_offset;
	m_radiusBS = 0.f;
}
