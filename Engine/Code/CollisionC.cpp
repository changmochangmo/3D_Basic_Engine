#include "EngineStdafx.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Object.h"
#include "DataStore.h"

USING(Engine)
CCollisionC::CCollisionC(void)
{
}

CCollisionC::~CCollisionC(void)
{
	OnDestroy();
}

SP(CComponent) CCollisionC::MakeClone(CObject* pObject)
{
	SP(CCollisionC) spClone(new CCollisionC);
	__super::InitClone(spClone, pObject);

	spClone->SetCollisionID(m_collisionID);
	for (auto& collider : m_vColliders)
		spClone->AddColliderClone(collider->MakeClone(spClone.get()));
	
	return spClone;
}

void CCollisionC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic = m_pOwner->GetIsStatic();
		_int dataID = m_pOwner->GetDataID();
		std::wstring objectKey = m_pOwner->GetObjectKey();

		GET_VALUE(isStatic, dataID, objectKey, L"collisionID", m_collisionID);
		AddColliderFromFile();
	}
}

void CCollisionC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_spTransform = m_pOwner->GetComponent<CTransformC>();
	m_spRigidbody = m_pOwner->GetComponent<CRigidBodyC>();

	CCollisionManager::GetInstance()->AddCollisionToManager(std::dynamic_pointer_cast<CCollisionC>(spThis));
}

void CCollisionC::FixedUpdate(SP(CComponent) spThis)
{
}

void CCollisionC::Update(SP(CComponent) spThis)
{
	if (m_spTransform->GetHasChanged())
	{
		UpdateOwnerRotMat();
		for (auto& collider : m_vColliders)
			collider->UpdatePosition();
	}
}

void CCollisionC::LateUpdate(SP(CComponent) spSelf)
{
}

void CCollisionC::OnDestroy(void)
{
	for (auto& collider : m_vColliders)
		collider->Free();

	m_vColliders.clear();
}

void CCollisionC::OnEnable(void)
{
}

void CCollisionC::OnDisable(void)
{
}

void CCollisionC::AddCollider(CCollider* pCollider)
{
	pCollider->SetOwner(this);
	m_vColliders.emplace_back(pCollider);

	if (m_radiusBS == UNDEFINED)
	{
		m_offsetBS = pCollider->GetOffset();
		m_radiusBS = pCollider->GetRadiusBS();
	}
	else
		MergingBS(pCollider);

	SP(CDebugC) spDebugC = m_pOwner->GetComponent<CDebugC>();
	if (spDebugC != nullptr)
		spDebugC->AddDebugCollider(pCollider);
}

void CCollisionC::AddColliderClone(CCollider* pCollider)
{
	m_vColliders.emplace_back(pCollider);
}

void CCollisionC::AddCollisionInfo(_CollisionInfo collisionInfo)
{
	m_vCurCollisions.emplace_back(collisionInfo);
}

void CCollisionC::AddTriggeredCC(CCollisionC* pCC)
{
	m_vCurTriggers.emplace_back(pCC);
}

void CCollisionC::AddColliderFromFile(void)
{
	_bool			isStatic	= m_pOwner->GetIsStatic();
	_int			dataID		= m_pOwner->GetDataID();
	std::wstring	objectKey	= m_pOwner->GetObjectKey();
	std::wstring	varKey;


	for (_int i = 0; i < (_int)EColliderType::NumOfCT; ++i)
	{
		_int numOfCollider;
		varKey = L"numOf_Type" + std::to_wstring(i) + L"_Collider";
		GET_VALUE(isStatic, dataID, objectKey, varKey, numOfCollider);

		CCollider* pCollider;
		_float3 offset;
		for (_int j = 0; j < numOfCollider; ++j)
		{
			std::wstring index = std::to_wstring(j);
			switch (i)
			{
			case (_int)EColliderType::Point:
			{
				GET_VALUE(isStatic, dataID, objectKey, L"pointCollider_" + index + L"_offset", offset);
				pCollider = CPointCollider::Create(offset);
				break;
			}
			case (_int)EColliderType::Ray:
			{
				_float3 dir;
				_float len;
				GET_VALUE(isStatic, dataID, objectKey, L"RayCollider_" + index + L"_offset", offset);
				GET_VALUE(isStatic, dataID, objectKey, L"RayCollider_" + index + L"_dir", dir);
				GET_VALUE(isStatic, dataID, objectKey, L"RayCollider_" + index + L"_len", len);
				pCollider = CRayCollider::Create(offset, dir, len);
				break;
			}
			case (_int)EColliderType::Sphere:
			{
				_float radius;
				GET_VALUE(isStatic, dataID, objectKey, L"SphereCollider_" + index + L"_radius", radius);
				GET_VALUE(isStatic, dataID, objectKey, L"SphereCollider_" + index + L"_offset", offset);

				pCollider = CSphereCollider::Create(radius, offset);
				break;
			}
			case (_int)EColliderType::AABB:
			{
				_float3 size;
				GET_VALUE(isStatic, dataID, objectKey, L"AabbCollider_" + index + L"_size", size);
				GET_VALUE(isStatic, dataID, objectKey, L"AabbCollider_" + index + L"_offset", offset);

				pCollider = CAabbCollider::Create(size, offset);
				break;
			}
			case (_int)EColliderType::OBB:
			{
				_float3 size, right, up, forward;
				GET_VALUE(isStatic, dataID, objectKey, L"ObbCollider_" + index + L"_size", size);
				GET_VALUE(isStatic, dataID, objectKey, L"ObbCollider_" + index + L"_offset", offset);

				pCollider = CObbCollider::Create(size, offset, right, up, forward);
				break;
			}
			default:
			{
				MSG_BOX(__FILE__, L"EColliderType::NumOfCT is broken");
				ABORT;
				break;
			}
			}

			AddCollider(pCollider);
		}
	}
}

void CCollisionC::MergingBS(CCollider* pCollider)
{
	_float3 curOffset = pCollider->GetOffset();
	_float curRadius = pCollider->GetRadiusBS();

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

void CCollisionC::UpdateOwnerRotMat(void)
{
	_mat rotateX, rotateY, rotateZ, rotate;
	D3DXMatrixRotationX(&rotateX, m_spTransform->GetRotation().x);
	D3DXMatrixRotationY(&rotateY, m_spTransform->GetRotation().y);
	D3DXMatrixRotationZ(&rotateZ, m_spTransform->GetRotation().z);

	m_ownerRotMat = rotateX * rotateY * rotateZ;
}

void CCollisionC::ProcessCollisions(void)
{
	if (m_vCurCollisions.size() == 0 && m_vPreCollisions.size() == 0)
		return;

	for (auto& curColInfo : m_vCurCollisions)
	{
		_bool alreadyThere = false;
		for (auto& it = m_vPreCollisions.begin(); it != m_vPreCollisions.end(); ++it)
		{
			CCollisionC* pPreCollidedCC = (*it).pOtherCollider->GetOwner();
			CCollisionC* pCurCollidedCC = curColInfo.pOtherCollider->GetOwner();
			if (pPreCollidedCC == pCurCollidedCC)
			{
				m_pOwner->OnCollisionStay(curColInfo);
				alreadyThere = true;
				m_vPreCollisions.erase(it);
				break;
			}
		}

		if (alreadyThere == false)
			m_pOwner->OnCollisionEnter(curColInfo);
	}

	for (auto& preColInfo : m_vPreCollisions)
		m_pOwner->OnCollisionExit(preColInfo);

	m_vPreCollisions.clear();
	m_vPreCollisions = m_vCurCollisions;
	m_vCurCollisions.clear();
}

void CCollisionC::ProcessTriggers(void)
{
	if (m_vCurTriggers.size() == 0 && m_vPreTriggers.size() == 0)
		return;

	for (auto& curTrigger : m_vCurTriggers)
	{
		_bool alreadyThere = false;
		for (auto& it = m_vPreTriggers.begin(); it != m_vPreTriggers.end(); ++it)
		{
			if ((*it) == curTrigger)
			{
				m_pOwner->OnTriggerStay(curTrigger);
				alreadyThere = true;
				m_vPreTriggers.erase(it);
				break;
			}
		}

		if (alreadyThere == false)
			m_pOwner->OnTriggerEnter(curTrigger);
	}

	for (auto& preTrigger : m_vPreTriggers)
		m_pOwner->OnTriggerExit(preTrigger);

	m_vPreTriggers.clear();
	m_vPreTriggers = m_vCurTriggers;
	m_vCurTriggers.clear();
}

