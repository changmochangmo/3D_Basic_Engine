#include "EngineStdafx.h"
#include "SphereCollider.h"
#include "ColliderManager.h"
#include "GameObject.h"

USING(Engine)
CSphereCollider::CSphereCollider(void)
{
}

CSphereCollider::~CSphereCollider(void)
{
}

CSphereCollider* CSphereCollider::Create(_float radius, _float3 offset)
{
	CSphereCollider* pSphere = new CSphereCollider();
	pSphere->SetRadius(radius);
	pSphere->SetOffset(offset);
	pSphere->Awake();

	return pSphere;
}

void CSphereCollider::Free(void)
{
	delete this;
}

CCollider * CSphereCollider::MakeClone(CCollisionC * pCC)
{
	CSphereCollider* pSC = CSphereCollider::Create(m_radius, m_offset);
	pSC->SetOwner(pCC);

	return pSC;
}

void CSphereCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_int)EColliderType::Sphere;
}

void CSphereCollider::OnDestroy(void)
{
}

void CSphereCollider::OnEnable(void)
{
}

void CSphereCollider::OnDisable(void)
{
}

void CSphereCollider::MakeBS(void)
{
	m_offsetBS = m_offset;
	m_radiusBS = m_radius;
}
