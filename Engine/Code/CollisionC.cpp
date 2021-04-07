#include "EngineStdafx.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "GameObject.h"
#include "DataStore.h"

USING(Engine)
CCollisionC::CCollisionC(void)
{
}

CCollisionC::~CCollisionC(void)
{
	OnDestroy();
}

SP(CComponent) CCollisionC::MakeClone(CGameObject* pObject)
{
	SP(CCollisionC) spClone(new CCollisionC);
	__super::InitClone(spClone, pObject);

	spClone->SetColliderID(m_colliderID);

	for (auto& collider : m_vColliders)
		spClone->AddCollider(collider->MakeClone(spClone.get()));


	return spClone;
}

void CCollisionC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;
}

void CCollisionC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_pTransform = m_pOwner->GetComponent<CTransformC>();


	_bool isStatic = m_pOwner->GetIsStatic();
	_int ownerDataID = m_pOwner->GetDataID();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if (m_colliderID == 0)
		GET_VALUE(isStatic, ownerDataID, objectKey, L"colliderID", m_colliderID);

	CColliderManager::GetInstance()->AddColliderToManager(std::dynamic_pointer_cast<CCollisionC>(spThis));

	CalculateBS();
}

void CCollisionC::FixedUpdate(SP(CComponent) spThis)
{
	//std::vector<_int>& layersToCheck = CColliderManager::GetInstance()->GetLayersToCheck(m_colliderID);
	//
	//for (int i = 0; i < layersToCheck.size(); ++i)
	//{
	//	for (auto& myCollider : m_vColliders)
	//	{
	//
	//	}
	//}
}

void CCollisionC::Update(SP(CComponent) spThis)
{
}

void CCollisionC::LateUpdate(SP(CComponent) spSelf)
{
}

void CCollisionC::OnDestroy(void)
{
	for (auto& collider : m_vColliders)
		delete collider;

	m_vColliders.clear();
}

void CCollisionC::OnEnable(void)
{
}

void CCollisionC::OnDisable(void)
{
}

CCollisionC* CCollisionC::AddCollider(CCollider* pCollider)
{
	pCollider->SetOwner(this);
	m_vColliders.emplace_back(pCollider);

	return this;
}

void CCollisionC::CalculateBS(void)
{
	for (auto& collider : m_vColliders)
		MergingTwoBS(collider->GetOffsetBS(), collider->GetRadiusBS());
}

void CCollisionC::MergingTwoBS(_float3 curOffset, _float curRadius)
{
	_float3 delta = m_offsetBS - curOffset;
	_float sqDist = D3DXVec3Dot(&delta, &delta);

	if ((m_radiusBS - curRadius) * (m_radiusBS - curRadius) >= sqDist)
	{
		if (m_radiusBS < curRadius)
			m_radiusBS = curRadius;
	}
	else
	{
		_float dist = sqrt(sqDist);
		m_radiusBS = (dist + curRadius + m_radiusBS) * 0.5f;
		m_offsetBS = curOffset;
		if (dist > EPSILON)
			m_offsetBS += ((m_radiusBS - curRadius) / dist) * delta;
	}

}

