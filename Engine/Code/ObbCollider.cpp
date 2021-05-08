#include "EngineStdafx.h"
#include "ObbCollider.h"


USING(Engine)
CObbCollider::CObbCollider()
{
}


CObbCollider::~CObbCollider()
{
}

CObbCollider * CObbCollider::Create(_float3 size, _float3 offset,
									_float3 right, _float3 up, _float3 forward)
{
	CObbCollider* pObb = new CObbCollider;
	pObb->SetOffset(offset);
	pObb->SetSize(size);
	pObb->SetHalfSize(size / 2.f);
	pObb->SetRight(right);
	pObb->SetUp(up);
	pObb->SetForward(forward);

	pObb->Awake();

	return pObb;
}

CCollider * CObbCollider::MakeClone(CCollisionC * pCC)
{
	CObbCollider* pObbClone = new CObbCollider;
	
	//Create 
	pObbClone->SetOffset(m_offset);
	pObbClone->SetSize(m_size);
	pObbClone->SetHalfSize(m_halfSize);

	//Awake
	pObbClone->SetRadiusBS(m_radiusBS);
	pObbClone->SetColliderType(m_colliderType);

	//MakeClone
	pObbClone->SetOwner(pCC);

	return pObbClone;
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

void CObbCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
	
	SP(CTransformC) spOwnerTransform = m_pOwner->GetTransform();
	m_right		= spOwnerTransform->GetRight();
	m_up		= spOwnerTransform->GetUp();
	m_forward	= spOwnerTransform->GetForward();
}

_float CObbCollider::SqDistFromPoint(_float3 const& point)
{
	_float3 closest = ClosestFromPoint(point);

	return D3DXVec3Dot(&(closest - point), &(closest - point));
}

_float3 CObbCollider::ClosestFromPoint(_float3 const& point)
{
	_float3 center = m_pOwner->GetTransform()->GetPosition() + m_offset;
	_float3 dir = point - center;

	_float3 closest = center;
	
	_mat worldMat = m_pOwner->GetTransform()->GetWorldMatrix();

	_float3 orientedAxis[3] = {};
	D3DXVec3TransformNormal(&orientedAxis[0], &m_right, &worldMat);
	D3DXVec3TransformNormal(&orientedAxis[1], &m_up, &worldMat);
	D3DXVec3TransformNormal(&orientedAxis[2], &m_forward, &worldMat);
	

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

//검증 필요
_float3 CObbCollider::SurfacePoint(_float3 const & dir)
{
	_float dotDirRight		= D3DXVec3Dot(&dir, &m_right);
	_float dotDirUp			= D3DXVec3Dot(&dir, &m_up);
	_float dotDirForward	= D3DXVec3Dot(&dir, &m_forward);

	_float3 projOnRight		= dotDirRight * m_right;
	_float3 projOnUp		= dotDirUp * m_up;
	_float3 projOnForward	= dotDirForward * m_forward;

	_float porSize	= D3DXVec3Length(&projOnRight);
	_float pouSize	= D3DXVec3Length(&projOnUp);
	_float pofSize	= D3DXVec3Length(&projOnForward);

	SP(CTransformC) spTransform = m_pOwner->GetTransform();
	_float3 hitPoint;
	_float3 proportion(porSize / m_halfSize.x, pouSize / m_halfSize.y, pofSize / m_halfSize.z);

	if (proportion.x > proportion.y && proportion.x > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.x;
	else if (proportion.y > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.y;
	else
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.z;

	return hitPoint;
}

void CObbCollider::MakeBS(void)
{
	_float3 minPos = m_offset - m_halfSize;
	_float3 maxPos = m_offset + m_halfSize;

	m_radiusBS = D3DXVec3Length(&(maxPos - minPos)) / 2.f;
}
