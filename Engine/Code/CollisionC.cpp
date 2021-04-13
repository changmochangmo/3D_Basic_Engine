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

	spClone->SetCollisionID(m_collisionID);
	for (auto& collider : m_vColliders)
		spClone->AddColliderClone(collider->MakeClone(spClone.get()));
	
	return spClone;
}

void CCollisionC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;

	_bool isStatic			= m_pOwner->GetIsStatic();
	_int ownerDataID		= m_pOwner->GetDataID();
	std::wstring objectKey	= m_pOwner->GetObjectKey();

	GET_VALUE(isStatic, ownerDataID, objectKey, L"collisionID", m_collisionID);

	AddColliderFromFile();
}

void CCollisionC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_spTransform = m_pOwner->GetComponent<CTransformC>();
	m_spRigidbody = m_pOwner->GetComponent<CRigidBodyC>();

	CColliderManager::GetInstance()->AddCollisionToManager(std::dynamic_pointer_cast<CCollisionC>(spThis));
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
}

void CCollisionC::AddColliderClone(CCollider* pCollider)
{
	m_vColliders.emplace_back(pCollider);
}

void CCollisionC::AddCollisionInfo(_CollisionInfo collisionInfo)
{
	m_vCurCollisions.emplace_back(collisionInfo);
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

