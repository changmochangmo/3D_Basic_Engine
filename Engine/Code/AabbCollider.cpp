#include "EngineStdafx.h"
#include "AabbCollider.h"

USING(Engine)
CAabbCollider::CAabbCollider()
{
}


CAabbCollider::~CAabbCollider()
{
}

CAabbCollider * CAabbCollider::Create(_float3 size, _float3 offset)
{
	CAabbCollider*	pAabb = new CAabbCollider;
	pAabb->SetOffset(offset);
	pAabb->SetSize(size);
	pAabb->SetHalfSize(size / 2.f);
	pAabb->Awake();

	return pAabb;
}

CCollider * CAabbCollider::MakeClone(CColliderComponent * pCC)
{
	CAabbCollider* pAC = CAabbCollider::Create(m_size, m_offset);
	pAC->SetOwner(pCC);

	return pAC;
}

void CAabbCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_uint)EColliderType::AABB;
}

void CAabbCollider::OnDestroy(void)
{
}

void CAabbCollider::OnEnable(void)
{
}

void CAabbCollider::OnDisable(void)
{
}

_float CAabbCollider::SqDistFromPoint(_float3 point)
{
	_float sqDist = 0.f;
	
	_float3 minPos = m_pOwner->GetTransform()->GetPosition() + m_offset - m_halfSize;
	_float3 maxPos = m_pOwner->GetTransform()->GetPosition() + m_offset + m_halfSize;

	for (int i = 0; i < 3; ++i)
	{
		if (point[i] < minPos[i]) sqDist += (minPos[i] - point[i]) * (minPos[i] - point[i]);
		if (point[i] > maxPos[i]) sqDist += (point[i] - maxPos[i]) * (point[i] - maxPos[i]);
	}

	return sqDist;
}

_float3 CAabbCollider::ClosestFromPoint(_float3 point)
{
	_float3 closestPoint = {};

	_float3 minPos = m_pOwner->GetTransform()->GetPosition() + m_offset - m_halfSize;
	_float3 maxPos = m_pOwner->GetTransform()->GetPosition() + m_offset + m_halfSize;

	for (int i = 0; i < 3; ++i)
	{
		if (point[i] < minPos[i]) point[i] = minPos[i];
		else if (point[i] > maxPos[i])	 point[i] = maxPos[i];

		closestPoint[i] = point[i];
	}

	return closestPoint;
}

void CAabbCollider::MakeBS(void)
{
	_float3 minPos = m_offset - m_halfSize;
	_float3 maxPos = m_offset + m_halfSize;

	m_offsetBS = m_offset;
	m_radiusBS = D3DXVec3Length(&(maxPos - minPos)) / 2.f;
}
