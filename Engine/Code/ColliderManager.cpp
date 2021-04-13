#include "EngineStdafx.h"
#include "ColliderManager.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "CollisionHelper.h"
#include "DataStore.h"
#include "FRC.h"


USING(Engine)
IMPLEMENT_SINGLETON(CColliderManager)

void CColliderManager::Awake(void)
{
	__super::Awake();
	InitCollisionChecker();
}

void CColliderManager::Start(_int numOfColliderID)
{
	m_numOfColliderID = numOfColliderID;
	for (int i = 0; i < m_numOfColliderID; ++i)
	{
		std::vector<SP(CCollisionC)> colliders;
		m_vColliderComponents.emplace_back(colliders);

		std::vector<_int> collisionMap;
		m_vCollisionMap.emplace_back(collisionMap);
	}

	InitCollisionMap();
}

void CColliderManager::FixedUpdate(void)
{
}

void CColliderManager::Update(void)
{
}

void CColliderManager::LateUpdate(void)
{
	for (int i = 0; i < m_numOfColliderID; ++i)
	{
		for (auto& it = m_vColliderComponents[i].begin(); it != m_vColliderComponents[i].end();)
		{
			if ((*it)->GetOwner() == nullptr)
			{
				(*it).reset();
				it = m_vColliderComponents[i].erase(it);
			}
			else
				++it;
		}
	}
}


void CColliderManager::OnDestroy(void)
{
	m_vColliderComponents.clear();
}

void CColliderManager::OnEnable(void)
{
}

void CColliderManager::OnDisable(void)
{
}

void CColliderManager::CheckCollision(CCollisionC* pCC)
{
	std::vector<_int>& checkingLayer = GetLayersToCheck(pCC->GetCollisionID());
	_bool isItCollided;

	for (auto& layerID : checkingLayer)
	{
		for (auto& ccIt : m_vColliderComponents[layerID])
		{
			if (ccIt.get() == pCC)
				continue;

			if (pCC->GetTransform() == nullptr)
			{
				MSG_BOX(__FILE__, L"콜라이더 컴포넌트에 트랜스폼이 없다.");
				ABORT;
			}
			else if (pCC->GetRigidbody() == nullptr)
			{
				MSG_BOX(__FILE__, L"콜라이더 컴포넌트에 리지드 바디가 없네요.");
				ABORT;
			}
			
			//콜리션 컴포넌트 간의 BS 체크
			if (CollisionHelper::CheckCollisionComponentBS(pCC, ccIt.get()) == false)
				continue;

			isItCollided = false;
			for (auto& checkCollider : ccIt->GetColliders())
			{
				for (auto& myCollider : pCC->GetColliders())
				{
					//콜라이더 간의 BS 체크
					if (CollisionHelper::CheckColliderBS(myCollider, checkCollider) == false)
						continue;

					_int myCType = myCollider->GetColliderType();
					_int checkCType = checkCollider->GetColliderType();
					if (isItCollided = (m_fpCollisionChecker[myCType][checkCType])(myCollider, checkCollider))
						break;
				}
				if (isItCollided)
					break;
			}
		}
	}
}

void CColliderManager::AddCollisionToManager(SP(CCollisionC) colliderComponent)
{
	if (colliderComponent == nullptr)
		return;

	m_vColliderComponents[colliderComponent->GetCollisionID()].emplace_back(colliderComponent);
}

std::vector<_int>& CColliderManager::GetLayersToCheck(_int colliderID)
{
	return m_vCollisionMap[colliderID];
}

void CColliderManager::InitCollisionChecker(void)
{
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::Point]	= CollisionHelper::PointPoint;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::Ray]		= CollisionHelper::PointRay;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::Sphere]	= CollisionHelper::PointSphere;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::AABB]		= CollisionHelper::PointAabb;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::OBB]		= CollisionHelper::PointObb;

	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::Point]		= CollisionHelper::PointRay;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::Ray]		= CollisionHelper::RayRay;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::Sphere]		= CollisionHelper::RaySphere;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::AABB]		= CollisionHelper::RayAabb;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::OBB]		= CollisionHelper::RayObb;

	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::Point]	= CollisionHelper::PointSphere;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::Ray]		= CollisionHelper::RaySphere;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::Sphere]	= CollisionHelper::SphereSphere;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::AABB]	= CollisionHelper::SphereAabb;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::OBB]		= CollisionHelper::SphereObb;

	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::Point]		= CollisionHelper::PointAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::Ray]		= CollisionHelper::RayAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::Sphere]	= CollisionHelper::SphereAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::AABB]		= CollisionHelper::AabbAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::OBB]		= CollisionHelper::AabbObb;

	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::Point]		= CollisionHelper::PointObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::Ray]		= CollisionHelper::RayObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::Sphere]		= CollisionHelper::SphereObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::AABB]		= CollisionHelper::AabbObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::OBB]		= CollisionHelper::ObbObb;
}

void CColliderManager::InitCollisionMap(void)
{
	for (_uint i = 0; i < m_vCollisionMap.size(); ++i)
	{
		_int numOfLayerToCheck = 0;
		std::wstring varKey = L"numOfLayerToCheck" + std::to_wstring(i);
		GET_VALUE(true, m_dataID, m_objectKey, varKey, numOfLayerToCheck);

		for (_int j = 0; j < numOfLayerToCheck; ++j)
		{
			_int checkLayer = -1;
			varKey = L"Layer" + std::to_wstring(i) + L"_Check" + std::to_wstring(j);
			GET_VALUE(true, m_dataID, m_objectKey, varKey, checkLayer);

			m_vCollisionMap[i].push_back(checkLayer);
		}
	}
	int a = 0;
	return;
}