#include "EngineStdafx.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "Object.h"

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
	pSphere->SetOffsetOrigin(offset);
	pSphere->Awake();

	return pSphere;
}

CCollider * CSphereCollider::MakeClone(CCollisionC * pCC)
{
	CSphereCollider* pSphereClone = new CSphereCollider;
	pSphereClone->SetOffsetOrigin(m_offsetOrigin);
	pSphereClone->SetRadius(m_radius);

	pSphereClone->SetRadiusBS(m_radiusBS);

	pSphereClone->SetColliderType(m_colliderType);

	pSphereClone->SetOwner(pCC);

	return pSphereClone;
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

void CSphereCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
}

void CSphereCollider::MakeBS(void)
{
	m_radiusBS = m_radius;
}
