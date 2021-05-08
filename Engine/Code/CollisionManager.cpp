#include "EngineStdafx.h"
#include "CollisionManager.h"
#include "SphereCollider.h"
#include "Object.h"
#include "CollisionHelper.h"
#include "DataStore.h"
#include "FRC.h"


USING(Engine)
IMPLEMENT_SINGLETON(CCollisionManager)

void CCollisionManager::Awake(void)
{
	__super::Awake();
	InitCollisionChecker();
}

void CCollisionManager::Start(_int numOfColliderID)
{
	m_numOfColliderID = numOfColliderID;
	for (int i = 0; i < m_numOfColliderID; ++i)
	{
		std::vector<SP(CCollisionC)> colliders;
		m_vCollisionComponents.emplace_back(colliders);

		std::vector<_int> collisionMap;
		m_vCollisionMap.emplace_back(collisionMap);
	}

	InitCollisionMap();
}

void CCollisionManager::FixedUpdate(void)
{
}

void CCollisionManager::Update(void)
{
	for (_int i = 0; i < m_numOfColliderID; ++i)
	{
		for (auto& spCC : m_vCollisionComponents[i])
		{
			//모든 CollisionComponent가 CheckCollision을 한다면,
			//하나의 충돌에 대해서 양쪽 CollisionComponent가 CollisionInfo를 쏠 거야.
			//ANS: Layer1이 Layer2를 체크해야할 레이어로 놓는다면
			//Layer2는 Layer1을 체크해야할 레이어에 놓지 않으면 됨.
			CheckCollision(spCC.get());
		}
	}

	for (_int i = 0; i < m_numOfColliderID; ++i)
	{
		for (auto& spCC : m_vCollisionComponents[i])
		{
			spCC->ProcessCollisions();
			spCC->ProcessTriggers();
		}
	}
}

void CCollisionManager::LateUpdate(void)
{
	for (int i = 0; i < m_numOfColliderID; ++i)
	{
		for (auto& it = m_vCollisionComponents[i].begin(); it != m_vCollisionComponents[i].end();)
		{
			if ((*it)->GetOwner() == nullptr)
			{
				(*it).reset();
				it = m_vCollisionComponents[i].erase(it);
			}
			else
				++it;
		}
	}
}


void CCollisionManager::OnDestroy(void)
{
	m_vCollisionComponents.clear();
}

void CCollisionManager::OnEnable(void)
{
}

void CCollisionManager::OnDisable(void)
{
}
void CCollisionManager::CheckCollision(CCollisionC* pCC)
{
	if (pCC == nullptr)
		return;

	if (pCC->GetTransform() == nullptr)
	{
		MSG_BOX(__FILE__, L"콜라이더 컴포넌트에 트랜스폼이 없다.");
		ABORT;
	}

	std::vector<_int>& checkingLayer = GetLayersToCheck(pCC->GetCollisionID());
	_bool isItCollided;

	for (auto& layerID : checkingLayer)
	{
		for (auto& ccIt : m_vCollisionComponents[layerID])
		{
			if (ccIt.get() == pCC)
				continue;

			
			
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

void CCollisionManager::AddCollisionToManager(SP(CCollisionC) colliderComponent)
{
	if (colliderComponent == nullptr)
		return;

	m_vCollisionComponents[colliderComponent->GetCollisionID()].emplace_back(colliderComponent);
}

std::vector<_int>& CCollisionManager::GetLayersToCheck(_int colliderID)
{
	return m_vCollisionMap[colliderID];
}

void CCollisionManager::InitCollisionChecker(void)
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

void CCollisionManager::InitCollisionMap(void)
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