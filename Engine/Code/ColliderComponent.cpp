#include "EngineStdafx.h"
#include "ColliderComponent.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "GameObject.h"
#include "DataStore.h"
USING(Engine)

CColliderComponent::CColliderComponent(void)
{
}

CColliderComponent::~CColliderComponent(void)
{
	OnDestroy();
}

SHARED(CComponent) CColliderComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CColliderComponent) pClone(new CColliderComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);
	pClone->SetIsAwaked(m_isAwaked);
	pClone->SetColliderID(m_colliderID);

	for (auto& collider : m_vColliders)
		pClone->AddCollider(collider->MakeClone(pClone.get()));


	return pClone;
}

void CColliderComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
}

void CColliderComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);

	m_pTransform = m_pOwner->GetComponent<CTransformComponent>();

	if (m_pOwner->GetMainComponent() != nullptr)
	{
		_bool isStatic = m_pOwner->GetIsStatic();
		std::wstring layerKey = m_pOwner->GetLayerKey();
		std::wstring objectKey = m_pOwner->GetObjectKey();

		if(m_colliderID == 0)
			GET_VALUE(isStatic, layerKey, objectKey, L"m_colliderID", m_colliderID);
	}
	CColliderManager::GetInstance()->AddColliderToManager(std::dynamic_pointer_cast<CColliderComponent>(spThis));

	CalculateBS();
}

_uint CColliderComponent::FixedUpdate(SHARED(CComponent) spThis)
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
	return _uint();
}

_uint CColliderComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CColliderComponent::LateUpdate(SHARED(CComponent) spSelf)
{
	return _uint();
}

void CColliderComponent::OnDestroy(void)
{
	for (auto& collider : m_vColliders)
		delete collider;

	m_vColliders.clear();
}

void CColliderComponent::OnEnable(void)
{
}

void CColliderComponent::OnDisable(void)
{
}

CColliderComponent* CColliderComponent::AddCollider(CCollider* pCollider)
{
	pCollider->SetOwner(this);
	m_vColliders.emplace_back(pCollider);

	return this;
}

void CColliderComponent::CalculateBS(void)
{
	for (auto& collider : m_vColliders)
		MergingTwoBS(collider->GetOffsetBS(), collider->GetRadiusBS());
}

void CColliderComponent::MergingTwoBS(_float3 curOffset, _float curRadius)
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

