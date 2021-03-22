#include "EngineStdafx.h"
#include "ObbCollider.h"


USING(Engine)
CObbCollider::CObbCollider()
{
}


CObbCollider::~CObbCollider()
{
}

CObbCollider * CObbCollider::Create(_float3 size, _float3 offset)
{
	CObbCollider* pObb = new CObbCollider;
	pObb->SetOffset(offset);
	pObb->SetSize(size);
	pObb->SetHalfSize(size / 2.f);
	pObb->Awake();

	return pObb;
}

CCollider * CObbCollider::MakeClone(CColliderComponent * pCC)
{
	CObbCollider* pOC = CObbCollider::Create(m_size, m_offset);
	pOC->SetOwner(pCC);

	return pOC;
}

void CObbCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_uint)EColliderType::OBB;
}

void CObbCollider::OnDestroy(void)
{
}

void CObbCollider::OnEnable(void)
{
}

void CObbCollider::OnDisable(void)
{
}

_float CObbCollider::SqDistFromPoint(_float3 point)
{
	_float3 closest = ClosestFromPoint(point);

	return D3DXVec3Dot(&(closest - point), &(closest - point));
}

_float3 CObbCollider::ClosestFromPoint(_float3 point)
{
	_float3 center = m_pOwner->GetTransform()->GetPosition() + m_offset;
	_float3 dir = point - center;

	_float3 closest = center;
	
	_mat worldMat = m_pOwner->GetTransform()->GetWorldMatrix();

	_float3 orientedAxis[3] = {};
	D3DXVec3TransformNormal(&orientedAxis[0], &m_orientedX, &worldMat);
	D3DXVec3TransformNormal(&orientedAxis[1], &m_orientedY, &worldMat);
	D3DXVec3TransformNormal(&orientedAxis[2], &m_orientedZ, &worldMat);
	

	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3Normalize(&orientedAxis[i], &orientedAxis[i]);
		float dist = D3DXVec3Dot(&dir, &orientedAxis[i]);

		if (dist > m_halfSize[i]) dist = m_halfSize[i];
		if (dist < -m_halfSize[i]) dist = -m_halfSize[i];

		closest += (dist * orientedAxis[i]);
	}

	return closest;
}

void CObbCollider::MakeBS(void)
{
	_float3 minPos = m_offset - m_halfSize;
	_float3 maxPos = m_offset + m_halfSize;

	m_offsetBS = m_offset;
	m_radiusBS = D3DXVec3Length(&(maxPos - minPos)) / 2.f;
}
