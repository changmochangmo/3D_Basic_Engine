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

CCollider * CAabbCollider::MakeClone(CCollisionC * pCC)
{
	CAabbCollider* pAabbClone = new CAabbCollider;
	pAabbClone->SetOffset(m_offset);
	pAabbClone->SetSize(m_size);
	pAabbClone->SetHalfSize(m_halfSize);

	pAabbClone->SetRadiusBS(m_radiusBS);

	pAabbClone->SetColliderType(m_colliderType);

	pAabbClone->SetOwner(pCC);

	return pAabbClone;
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

_float CAabbCollider::SqDistFromPoint(_float3 const& point)
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

_float3 CAabbCollider::ClosestFromPoint(_float3 const& point)
{
	_float3 closestPoint = ZERO_VECTOR;

	_float3 minPos = m_pOwner->GetTransform()->GetPosition() + m_offset - m_halfSize;
	_float3 maxPos = m_pOwner->GetTransform()->GetPosition() + m_offset + m_halfSize;

	for (int i = 0; i < 3; ++i)
	{
		if (point[i] < minPos[i])		closestPoint[i] = minPos[i];
		else if (point[i] > maxPos[i])	closestPoint[i] = maxPos[i];
		else							closestPoint[i] = point[i];
		
	}
	/*for (int i = 0; i < 3; ++i)
	{
		if (point[i] < minPos[i]) point[i] = minPos[i];
		else if (point[i] > maxPos[i])	 point[i] = maxPos[i];

		closestPoint[i] = point[i];
	}*/

	return closestPoint;
}

_float3 CAabbCollider::SurfacePoint(_float3 const& dir)
{
	SP(CTransformC) spTransform = m_pOwner->GetTransform();
	_float3 hitPoint;
	_float3 proportion(abs(dir.x / m_halfSize.x), abs(dir.y / m_halfSize.y), abs(dir.z / m_halfSize.z));
	if (proportion.x > proportion.y && proportion.x > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.x;
	else if (proportion.y > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.y;
	else
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.z;

	return hitPoint;
}

void CAabbCollider::MakeBS(void)
{
	_float3 minPos = m_offset - m_halfSize;
	_float3 maxPos = m_offset + m_halfSize;

	m_radiusBS = D3DXVec3Length(&(maxPos - minPos)) / 2.f;
}
