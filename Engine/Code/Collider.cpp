#include "EngineStdafx.h"
#include "Collider.h"


USING(Engine)
CCollider::CCollider(void)
{
}

CCollider::~CCollider(void)
{
}

void CCollider::Free(void)
{
	OnDestroy();
	delete this;
}

void CCollider::Awake(void)
{
	MakeBS();
}

void CCollider::UpdatePosition(void)
{
	D3DXVec3TransformNormal(&m_position, &m_offset, &m_pOwner->GetOwnerRotMat());
	m_position += m_pOwner->GetTransform()->GetPosition();
}
