#ifndef COLLISIONHELPER_H
#define COLLISIONHELPER_H

#include "SceneManager.h"
#include "Layer.h"
#include "Object.h"

BEGIN(Engine)
BEGIN(CollisionHelper)

static _bool CollisionTypeSorting(CCollider* pC1, CCollider* pC2,
								  EColliderType supposedType1, EColliderType supposedType2,
								  CCollider*& pSortedC1, CCollider*& pSortedC2)
{
	if (pC1->GetColliderType() == (_int)supposedType1 && pC2->GetColliderType() == (_int)supposedType2)
	{
		pSortedC1 = pC1;
		pSortedC2 = pC2;

		return true;
	}
	else if (pC1->GetColliderType() == (_int)supposedType2 && pC2->GetColliderType() == (_int)supposedType1)
	{
		pSortedC1 = pC2;
		pSortedC2 = pC1;

		return true;
	}

	return false;
}

static _bool CheckBS(_float3 const& pos1, _float3 const& pos2,
					 _float const& radius1, _float const& radius2)
{
	_float3 posDelta = pos2 - pos1;
	_float sqDistance = D3DXVec3Dot(&posDelta, &posDelta);

	if (sqDistance > ((radius1 + radius2) * (radius1 + radius2)))
		return false;
	else
		return true;
}

static _bool CheckCollisionComponentBS(CCollisionC const* pCC1, CCollisionC const* pCC2)
{
	_float3 objOnePos = pCC1->GetTransform()->GetPosition();
	_float3 objTwoPos = pCC2->GetTransform()->GetPosition();

	_float3 ccOnePos = objOnePos + pCC1->GetOffsetBS();
	_float3 ccTwoPos = objTwoPos + pCC2->GetOffsetBS();

	_float radiusOne = pCC1->GetRadiusBS();
	_float radiusTwo = pCC2->GetRadiusBS();

	return CheckBS(ccOnePos, ccTwoPos, radiusOne, radiusTwo);
}

static _bool CheckColliderBS(CCollider const* pCollider1, CCollider const* pCollider2)
{
	_float3 objOnePos = pCollider1->GetOwner()->GetTransform()->GetPosition();
	_float3 objTwoPos = pCollider2->GetOwner()->GetTransform()->GetPosition();

	_float3 colliderOnePos = objOnePos + pCollider1->GetOffset();
	_float3 colliderTwoPos = objTwoPos + pCollider2->GetOffset();

	_float radiusOne = pCollider1->GetRadiusBS();
	_float radiusTwo = pCollider2->GetRadiusBS();

	return CheckBS(colliderOnePos, colliderTwoPos, radiusOne, radiusTwo);
}



static _bool PointPoint(CCollider* pC1, CCollider* pC2)
{
	SP(CTransformC) spTransform1 = pC1->GetOwner()->GetTransform();
	SP(CTransformC) spTransform2 = pC2->GetOwner()->GetTransform();

	CPointCollider* pPC1 = static_cast<CPointCollider*>(pC1);
	CPointCollider* pPC2 = static_cast<CPointCollider*>(pC2);

	if (spTransform1->GetPosition() + pPC1->GetOffset() ==
		spTransform2->GetPosition() + pPC2->GetOffset())
	{
		CCollisionC* pCC1 = pPC1->GetOwner();
		CCollisionC* pCC2 = pPC2->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			_float3 hitPoint = spTransform1->GetPosition() + pPC1->GetOffset();
			pPC1->GetOwner()->AddCollisionInfo(_CollisionInfo(pPC1, pPC2, hitPoint, ZERO_VECTOR, 0));
			pPC2->GetOwner()->AddCollisionInfo(_CollisionInfo(pPC2, pPC1, hitPoint, ZERO_VECTOR, 0));
		}
		
		return true;
	}

	return false;
}
static bool PointRay(CCollider* pC1, CCollider* pC2)
{
	CCollider* pSupposedPC = nullptr;
	CCollider* pSupposedRC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::Point, EColliderType::Ray, pSupposedPC, pSupposedRC))
		return false;

	CPointCollider* pPC = static_cast<CPointCollider*>(pSupposedPC);
	CRayCollider* pRC = static_cast<CRayCollider*>(pSupposedRC);

	SP(CTransformC) spPointTransform = pPC->GetOwner()->GetTransform();
	SP(CTransformC) spRayTransform = pRC->GetOwner()->GetTransform();

	_float3 rayStartPos = spRayTransform->GetPosition() + pRC->GetOffset();
	_float3 rayDir = pRC->GetDirection();
	_float3 pointPos = spPointTransform->GetPosition() + pPC->GetOffset();
	_float t = 0.f;

	_float3 rayStartToPoint = pointPos - rayStartPos;

	t = D3DXVec3Dot(&rayStartToPoint, &rayDir) / D3DXVec3Dot(&rayDir, &rayDir);

	
	if (rayStartPos + t * rayDir == pointPos)
	{
		CCollisionC* pCC1 = pPC->GetOwner();
		CCollisionC* pCC2 = pRC->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			pPC->GetOwner()->AddCollisionInfo(_CollisionInfo(pPC, pRC, pointPos, ZERO_VECTOR, 0));
			pRC->GetOwner()->AddCollisionInfo(_CollisionInfo(pRC, pPC, pointPos, ZERO_VECTOR, 0));
		}
		return true;
	}


	return false;
}
static bool PointSphere(CCollider* pC1, CCollider* pC2)
{ 
	CCollider* pSupposedPC = nullptr;
	CCollider* pSupposedSC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::Point, EColliderType::Sphere, pSupposedPC, pSupposedSC))
		return false;

	CPointCollider* pPC = static_cast<CPointCollider*>(pSupposedPC);
	CSphereCollider* pSC = static_cast<CSphereCollider*>(pSupposedSC);

	SP(CTransformC) spPointTransform = pPC->GetOwner()->GetTransform();
	SP(CTransformC) spSphereTransform = pSC->GetOwner()->GetTransform();

	_float3 scPosition = spSphereTransform->GetPosition() + pSC->GetOffset();
	_float3 pcPosition = spPointTransform->GetPosition() + pPC->GetOffset();

	if (D3DXVec3LengthSq(&(scPosition - pcPosition)) <= pSC->GetRadius() * pSC->GetRadius())
	{
		CCollisionC* pCC1 = pPC->GetOwner();
		CCollisionC* pCC2 = pSC->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			pPC->GetOwner()->AddCollisionInfo(_CollisionInfo(pPC, pSC, pcPosition, ZERO_VECTOR, 0));
			pSC->GetOwner()->AddCollisionInfo(_CollisionInfo(pSC, pPC, pcPosition, ZERO_VECTOR, 0));
		}
		return true;
	}

	return false; 
}

static bool PointAabb(CCollider* pC1, CCollider* pC2)
{ 
	CCollider* pSupposedPC = nullptr;
	CCollider* pSupposedAC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::Point, EColliderType::Sphere, pSupposedPC, pSupposedAC))
		return false;

	CPointCollider* pPC = static_cast<CPointCollider*>(pSupposedPC);
	CAabbCollider* pAC = static_cast<CAabbCollider*>(pSupposedAC);

	SP(CTransformC) spPointTransform = pPC->GetOwner()->GetTransform();
	SP(CTransformC) spAabbTransform = pAC->GetOwner()->GetTransform();

	_float3 pcPosition = spPointTransform->GetPosition() + pPC->GetOffset();
	_float3 acPosition = spAabbTransform->GetPosition() + pAC->GetOffset();
	_float3 acHalfSize = pAC->GetHalfSize();

	for (int i = 0; i < 3; ++i)
	{
		if (pcPosition[i] < acPosition[i] - acHalfSize[i]) return false;
		if (pcPosition[i] > acPosition[i] + acHalfSize[i]) return false;
	}

	CCollisionC* pCC1 = pPC->GetOwner();
	CCollisionC* pCC2 = pAC->GetOwner();

	if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
	{
		pCC1->AddTriggeredCC(pCC2);
		pCC2->AddTriggeredCC(pCC1);
	}
	else
	{
		pPC->GetOwner()->AddCollisionInfo(_CollisionInfo(pPC, pAC, pcPosition, ZERO_VECTOR, 0));
		pAC->GetOwner()->AddCollisionInfo(_CollisionInfo(pAC, pPC, pcPosition, ZERO_VECTOR, 0));
	}
	return true; 
}
static bool PointObb(CCollider* pC1, CCollider* pC2)
{ 
	CCollider* pSupposedPC = nullptr;
	CCollider* pSupposedOC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::Point, EColliderType::Sphere, pSupposedPC, pSupposedOC))
		return false;

	CPointCollider* pPC = static_cast<CPointCollider*>(pSupposedPC);
	CObbCollider* pOC = static_cast<CObbCollider*>(pSupposedOC);

	SP(CTransformC) spPointTransform = pPC->GetOwner()->GetTransform();
	SP(CTransformC) spObbTransform = pOC->GetOwner()->GetTransform();

	_float3 pcPosition = spPointTransform->GetPosition() + pPC->GetOffset();
	_float3 ocPosition = spObbTransform->GetPosition() + pOC->GetOffset();

	_float3 obbToPoint = pcPosition - ocPosition;
	_float3 closest = ocPosition;

	_float3 orientedAxis[3];
	orientedAxis[0] = pOC->GetRight();
	orientedAxis[1] = pOC->GetUp();
	orientedAxis[2] = pOC->GetForward();
	for (int i = 0; i < 3; ++i)
	{
		float distance = D3DXVec3Dot(&obbToPoint, &orientedAxis[i]);

		if (distance > pOC->GetHalfSize()[i]) distance = pOC->GetHalfSize()[i];
		if (distance < -pOC->GetHalfSize()[i]) distance = -pOC->GetHalfSize()[i];

		closest += distance * orientedAxis[i];
	}

	if (closest == pcPosition)
	{
		CCollisionC* pCC1 = pPC->GetOwner();
		CCollisionC* pCC2 = pOC->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			pPC->GetOwner()->AddCollisionInfo(_CollisionInfo(pPC, pOC, pcPosition, ZERO_VECTOR, 0));
			pOC->GetOwner()->AddCollisionInfo(_CollisionInfo(pOC, pPC, pcPosition, ZERO_VECTOR, 0));
		}
		return true;
	}

	return false; 
}

static bool RayRay(CCollider* pC1, CCollider* pC2)
{ 
	CRayCollider* pRC1 = static_cast<CRayCollider*>(pC1);
	CRayCollider* pRC2 = static_cast<CRayCollider*>(pC2);

	SP(CTransformC) spRayTransform1 = pRC1->GetOwner()->GetTransform();
	SP(CTransformC) spRayTransform2 = pRC2->GetOwner()->GetTransform();

	_float3 ray1Start = pRC1->GetOffset() + spRayTransform1->GetPosition();
	_float3 ray2Start = pRC2->GetOffset() + spRayTransform2->GetPosition();

	_float3 ray2StartToRay1Start = ray1Start - ray2Start;

	_float a = D3DXVec3Dot(&pRC1->GetDirection(), &pRC1->GetDirection());
	_float b = D3DXVec3Dot(&pRC1->GetDirection(), &pRC2->GetDirection());
	_float c = D3DXVec3Dot(&pRC1->GetDirection(), &ray2StartToRay1Start);
	_float d = D3DXVec3Dot(&pRC2->GetDirection(), &pRC2->GetDirection());
	_float e = D3DXVec3Dot(&pRC2->GetDirection(), &ray2StartToRay1Start);

	_float discriminant = (a * d) - (b * b);
	if (abs(discriminant) < EPSILON)
		return false;

	_float s = ((b * e) - (c * d)) / discriminant;
	_float t = ((a * e) - (b * c)) / discriminant;

	_float3 closestOnRay1 = ray1Start + pRC1->GetDirection() * s;
	_float3 closestOnRay2 = ray2Start + pRC2->GetDirection() * t;

	if (closestOnRay1 == closestOnRay2)
	{
		CCollisionC* pCC1 = pRC1->GetOwner();
		CCollisionC* pCC2 = pRC2->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			pRC1->GetOwner()->AddCollisionInfo(_CollisionInfo(pRC1, pRC2, closestOnRay1, ZERO_VECTOR, 0));
			pRC2->GetOwner()->AddCollisionInfo(_CollisionInfo(pRC2, pRC1, closestOnRay1, ZERO_VECTOR, 0));
		}
		return true;
	}

	return false; 
}
static bool RaySphere(CCollider* pC1, CCollider* pC2)
{ 
	CCollider* pSupposedRC = nullptr;
	CCollider* pSupposedSC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::Ray, EColliderType::Sphere, pSupposedRC, pSupposedSC))
		return false;

	CRayCollider* pRC = static_cast<CRayCollider*>(pSupposedRC);
	CSphereCollider* pSC = static_cast<CSphereCollider*>(pSupposedSC);

	SP(CTransformC) spRayTransform = pRC->GetOwner()->GetTransform();
	SP(CTransformC) spSphereTransform = pSC->GetOwner()->GetTransform();

	_float3 rayStartPos = spRayTransform->GetPosition() + pRC->GetOffset();
	_float3 spherePos = spSphereTransform->GetPosition() + pSC->GetOffset();

	_float3 m = rayStartPos - spherePos;
	
	_float b = D3DXVec3Dot(&m, &pRC->GetDirection());
	_float c = D3DXVec3Dot(&m, &m) - (pSC->GetRadius() * pSC->GetRadius());

	if (c > 0.f && b > 0.f) return false;

	float disc = b * b - c;
	if (disc < 0.f) return false;

	_float t = -b - sqrtf(disc);

	CCollisionC* pCC1 = pRC->GetOwner();
	CCollisionC* pCC2 = pSC->GetOwner();

	if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
	{
		pCC1->AddTriggeredCC(pCC2);
		pCC2->AddTriggeredCC(pCC1);
	}
	else
	{
		_float3 hitPoint = rayStartPos + t * pRC->GetDirection();
		pRC->GetOwner()->AddCollisionInfo(_CollisionInfo(pRC, pSC, hitPoint, ZERO_VECTOR, 0));
		pSC->GetOwner()->AddCollisionInfo(_CollisionInfo(pSC, pRC, hitPoint, ZERO_VECTOR, 0));
	}
	return true; 
}
static bool RayAabb(CCollider* pC1, CCollider* pC2)
{ 
	CCollider* pSupposedRC = nullptr;
	CCollider* pSupposedAC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::Ray, EColliderType::AABB, pSupposedRC, pSupposedAC))
		return false;

	CRayCollider* pRC = static_cast<CRayCollider*>(pSupposedRC);
	CAabbCollider* pAC = static_cast<CAabbCollider*>(pSupposedAC);

	SP(CTransformC) spRayTransform = pRC->GetOwner()->GetTransform();
	SP(CTransformC) spAabbTransform = pAC->GetOwner()->GetTransform();

	_float3 rayStartPos = spRayTransform->GetPosition() + pRC->GetOffset();
	_float3 aabbPos = spAabbTransform->GetPosition() + pAC->GetOffset();

	_float tMin = 0.f;
	_float tMax = pRC->GetLength();

	_float3 aabbMinPos = aabbPos - pAC->GetHalfSize();
	_float3 aabbMaxPos = aabbPos + pAC->GetHalfSize();

	for (int i = 0; i < 3; ++i)
	{
		if (abs(pRC->GetDirection()[i]) < EPSILON)
		{
			if ((rayStartPos[i] < aabbMinPos[i]) ||
				(rayStartPos[i] > aabbMaxPos[i]))
				return false;
		}
		else
		{
			_float ood = 1.f / pRC->GetDirection()[i];
			_float t1 = (aabbMinPos[i] - rayStartPos[i]) * ood;
			_float t2 = (aabbMaxPos[i] - rayStartPos[i]) * ood;

			if (t1 > t2)
			{
				_float temp = t1;
				t1 = t2;
				t2 = temp;
			}

			tMin = GET_MATH->Max(tMin, t1);
			tMax = GET_MATH->Min(tMax, t2);

			if (tMin > tMax) return false;
		}
	}


	CCollisionC* pCC1 = pRC->GetOwner();
	CCollisionC* pCC2 = pAC->GetOwner();

	if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
	{
		pCC1->AddTriggeredCC(pCC2);
		pCC2->AddTriggeredCC(pCC1);
	}
	else
	{
		//여기 왜 두번들어오냐
		_float3 normal			= pRC->GetDirection();
		_float3 rayHitPoint		= rayStartPos + pRC->GetDirection() * tMin;
		_float3 aabbHitPoint	= pAC->SurfacePointFromInside(-normal, rayHitPoint);
		_float penet			= D3DXVec3Length(&(rayHitPoint - aabbHitPoint));
		pRC->GetOwner()->AddCollisionInfo(_CollisionInfo(pRC, pAC, rayHitPoint, normal, penet));
		pAC->GetOwner()->AddCollisionInfo(_CollisionInfo(pAC, pRC, aabbHitPoint, -normal, penet));

		pRC->GetOwner()->GetOwner()->GetTransform()->AddPosition(-normal * penet);
	}

	return true; 
}
static bool RayObb(CCollider* pC1, CCollider* pC2)
{ 
	CCollider* pSupposedRC = nullptr;
	CCollider* pSupposedOC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::Ray, EColliderType::AABB, pSupposedRC, pSupposedOC))
		return false;

	CRayCollider* pRC = static_cast<CRayCollider*>(pSupposedRC);
	CAabbCollider* pOC = static_cast<CAabbCollider*>(pSupposedOC);

	SP(CTransformC) spRayTransform = pRC->GetOwner()->GetTransform();
	SP(CTransformC) spObbTransform = pOC->GetOwner()->GetTransform();

	_float3 rayStartPos = spRayTransform->GetPosition() + pRC->GetOffset();
	_float3 obbPos = spObbTransform->GetPosition() + pOC->GetOffset();

	_mat obbWorldMat = spObbTransform->GetWorldMatrix();

	_float tMin = -FLT_MAX;
	_float tMax = FLT_MAX;

	_float3 d = obbPos - rayStartPos;

	_float3 orientedAxis[3];
	orientedAxis[0] = _float3(obbWorldMat._11, obbWorldMat._12, obbWorldMat._13);
	orientedAxis[1] = _float3(obbWorldMat._21, obbWorldMat._22, obbWorldMat._23);
	orientedAxis[2] = _float3(obbWorldMat._31, obbWorldMat._32, obbWorldMat._33);

	_float3 aabbMinPos = obbPos - pOC->GetHalfSize();
	_float3 aabbMaxPos = obbPos + pOC->GetHalfSize();

	for (int i = 0; i < 3; ++i)
	{
		_float e = D3DXVec3Dot(&orientedAxis[i], &d);
		_float f = D3DXVec3Dot(&orientedAxis[i], &pRC->GetDirection());

		if (abs(f) < EPSILON)
		{
			if ((-e + aabbMinPos[i]) > 0.f || (-e + aabbMaxPos[i]) < 0.f)
				return false;
		}

		_float t1 = (e + aabbMinPos[i]) / f;
		_float t2 = (e + aabbMaxPos[i]) / f;

		if (t1 > t2)
		{
			_float temp = t1;
			t1 = t2;
			t2 = temp;
		}

		if (t2 < tMax)
			tMax = t2;
		if (t1 > tMin)
			tMin = t1;

		if (tMax < tMin)
			return false;
	}

	CCollisionC* pCC1 = pRC->GetOwner();
	CCollisionC* pCC2 = pOC->GetOwner();

	if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
	{
		pCC1->AddTriggeredCC(pCC2);
		pCC2->AddTriggeredCC(pCC1);
	}
	else
	{
		_float3 hitPoint = rayStartPos + tMin * pRC->GetDirection();
		pRC->GetOwner()->AddCollisionInfo(_CollisionInfo(pRC, pOC, hitPoint, ZERO_VECTOR, 0));
		pOC->GetOwner()->AddCollisionInfo(_CollisionInfo(pOC, pRC, hitPoint, ZERO_VECTOR, 0));
	}

	return true; 
}

static bool SphereSphere(CCollider* pC1, CCollider* pC2)
{ 
	CSphereCollider* pSC1 = static_cast<CSphereCollider*>(pC1);
	CSphereCollider* pSC2 = static_cast<CSphereCollider*>(pC2);

	SP(CTransformC) spSphereTransform1 = pSC1->GetOwner()->GetTransform();
	SP(CTransformC) spSphereTransform2 = pSC2->GetOwner()->GetTransform();

	_float3 center1 = spSphereTransform1->GetPosition() + pSC1->GetOffset();
	_float3 center2 = spSphereTransform2->GetPosition() + pSC2->GetOffset();

	_float sqDistanceCenter = D3DXVec3LengthSq(&(center1 - center2));

	if (sqDistanceCenter <= pow(pSC1->GetRadius() + pSC2->GetRadius(), 2))
	{
		CCollisionC* pCC1 = pSC1->GetOwner();
		CCollisionC* pCC2 = pSC2->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			_float3 normal;
			D3DXVec3Normalize(&normal, &(center2 - center1));

			_float3 hitPoint1 = center1 + (normal * pSC1->GetRadius());
			_float3 hitPoint2 = center2 + (-normal * pSC2->GetRadius());
			_float	penet = D3DXVec3Length(&(hitPoint2 - hitPoint1));
			pSC1->GetOwner()->AddCollisionInfo(_CollisionInfo(pSC1, pSC2, hitPoint1, normal, penet));
			pSC2->GetOwner()->AddCollisionInfo(_CollisionInfo(pSC2, pSC1, hitPoint2, -normal, penet));
		}
		return true;
	}
	else
		return false;
}

static bool SphereAabb(CCollider* pC1, CCollider* pC2) 
{ 
	CCollider* pSupposedAC = nullptr;
	CCollider* pSupposedSC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::AABB, EColliderType::Sphere, pSupposedAC, pSupposedSC))
		return false;

	CAabbCollider* pAC = static_cast<CAabbCollider*>(pSupposedAC);
	CSphereCollider* pSC = static_cast<CSphereCollider*>(pSupposedSC);

	SP(CTransformC) spAabbTransform = pAC->GetOwner()->GetTransform();
	SP(CTransformC) spSphereTransform = pSC->GetOwner()->GetTransform();

	_float3 sphereCenter	= spSphereTransform->GetPosition() + pSC->GetOffset();
	_float3 aabbCenter		= spAabbTransform->GetPosition() + pAC->GetOffset();

	_float sqDist = pAC->SqDistFromPoint(sphereCenter);

	if (sqDist <= pSC->GetRadius() * pSC->GetRadius())
	{
		CCollisionC* pCC1 = pSC->GetOwner();
		CCollisionC* pCC2 = pAC->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			_float3 normal;
			D3DXVec3Normalize(&normal, &(sphereCenter - aabbCenter));

			_float3 aabbHitPoint = pAC->SurfacePoint(normal);
			_float3 sphereHitPoint = sphereCenter + (-normal) * pSC->GetRadius();
			_float penet = D3DXVec3Length(&(aabbHitPoint - sphereHitPoint));

			pAC->GetOwner()->AddCollisionInfo(_CollisionInfo(pAC, pSC, aabbHitPoint, normal, penet));
			pSC->GetOwner()->AddCollisionInfo(_CollisionInfo(pSC, pAC, sphereHitPoint, -normal, penet));
		}
		return true;
	}
	else
		return false;
}
static bool SphereObb(CCollider* pC1, CCollider* pC2) 
{
	CCollider* pSupposedOC = nullptr;
	CCollider* pSupposedSC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::OBB, EColliderType::Sphere, pSupposedOC, pSupposedSC))
		return false;

	CObbCollider* pOC = static_cast<CObbCollider*>(pSupposedOC);
	CSphereCollider* pSC = static_cast<CSphereCollider*>(pSupposedSC);

	SP(CTransformC) spObbTransform = pOC->GetOwner()->GetTransform();
	SP(CTransformC) spSphereTransform = pSC->GetOwner()->GetTransform();

	_float3 sphereCenter = spSphereTransform->GetPosition() + pSC->GetOffset();
	_float3 obbCenter = spObbTransform->GetPosition() + pOC->GetOffset();

	_float3 closestOnOBB = pOC->ClosestFromPoint(sphereCenter);
	_float3 sphereToClosest = closestOnOBB - sphereCenter;

	if (D3DXVec3Dot(&sphereToClosest, &sphereToClosest) <= pSC->GetRadius() * pSC->GetRadius())
	{
		CCollisionC* pCC1 = pOC->GetOwner();
		CCollisionC* pCC2 = pSC->GetOwner();

		if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
		{
			pCC1->AddTriggeredCC(pCC2);
			pCC2->AddTriggeredCC(pCC1);
		}
		else
		{
			_float3 normal;
			D3DXVec3Normalize(&normal, &(sphereCenter - obbCenter));

			_float3 obbHitPoint = pOC->SurfacePoint(normal);
			_float3 sphereHitPoint = sphereCenter + (-normal) * pSC->GetRadius();
			_float	penet = D3DXVec3Length(&(obbHitPoint - sphereHitPoint));

			pOC->GetOwner()->AddCollisionInfo(_CollisionInfo(pOC, pSC, obbHitPoint, normal, penet));
			pSC->GetOwner()->AddCollisionInfo(_CollisionInfo(pSC, pOC, sphereHitPoint, -normal, penet));
		}
		return true;
	}
	else
		return false;
}

static bool AabbAabb(CCollider* pC1, CCollider* pC2) 
{ 
	CAabbCollider* pAC1 = static_cast<CAabbCollider*>(pC1);
	CAabbCollider* pAC2 = static_cast<CAabbCollider*>(pC2);

	SP(CTransformC) spAabbTransform1 = pAC1->GetOwner()->GetTransform();
	SP(CTransformC) spAabbTransform2 = pAC2->GetOwner()->GetTransform();

	_float3 aabb1Center = pAC1->GetOffset() + spAabbTransform1->GetPosition();
	_float3 aabb2Center = pAC2->GetOffset() + spAabbTransform2->GetPosition();

	_float3 basicAxis[3] = { _float3(1, 0, 0), _float3(0, 1, 0), _float3(0, 0, 1) };
	for (int i = 0; i < 3; ++i)
	{
		if(GET_MATH->SeparateAxisTest(basicAxis[i], aabb1Center[i] - pAC1->GetHalfSize()[i], 
													aabb1Center[i] + pAC1->GetHalfSize()[i],
													aabb2Center[i] - pAC2->GetHalfSize()[i],
													aabb2Center[i] + pAC2->GetHalfSize()[i]) == false)
			return false;
	}

	CCollisionC* pCC1 = pAC1->GetOwner();
	CCollisionC* pCC2 = pAC2->GetOwner();

	if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
	{
		pCC1->AddTriggeredCC(pCC2);
		pCC2->AddTriggeredCC(pCC1);
	}
	else
	{
		_float3 normal;
		D3DXVec3Normalize(&normal, &(aabb2Center - aabb1Center));

		//Calculate HitPoint 
		_float3 hitPoint1 = pAC1->SurfacePoint(normal);
		_float3 hitPoint2 = pAC2->SurfacePoint(-normal);
		_float	penet = D3DXVec3Length(&(hitPoint2 - hitPoint1));
		pAC1->GetOwner()->AddCollisionInfo(_CollisionInfo(pAC1, pAC2, hitPoint1, normal, penet));
		pAC2->GetOwner()->AddCollisionInfo(_CollisionInfo(pAC2, pAC1, hitPoint2, -normal, penet));
	}
	return true; 
}
static bool AabbObb(CCollider* pC1, CCollider* pC2) 
{ 
	CCollider* pSupposedOC = nullptr;
	CCollider* pSupposedAC = nullptr;

	if (!CollisionTypeSorting(pC1, pC2, EColliderType::OBB, EColliderType::AABB, pSupposedOC, pSupposedAC))
		return false;

	CAabbCollider* pAC = static_cast<CAabbCollider*>(pSupposedAC);
	CObbCollider* pOC = static_cast<CObbCollider*>(pSupposedOC);

	SP(CTransformC) spAabbTransform = pAC->GetOwner()->GetTransform();
	SP(CTransformC) spObbTransform = pOC->GetOwner()->GetTransform();

	_float3 aabbCenter = pAC->GetOffset() + spAabbTransform->GetPosition();
	_float3 obbCenter = pOC->GetOffset() + spObbTransform->GetPosition();

	_float3 aabbAxis[3];
	aabbAxis[0] = _float3(1.f, 0.f, 0.f);
	aabbAxis[1] = _float3(0.f, 1.f, 0.f);
	aabbAxis[2] = _float3(0.f, 0.f, 1.f);

	_float3 obbOrientedAxis[3];
	obbOrientedAxis[0] = pOC->GetRight();
	obbOrientedAxis[1] = pOC->GetUp();
	obbOrientedAxis[2] = pOC->GetForward();


	_float ra, rb;

	_float rotation[3][3] = { 0.f };
	_float absRotation[3][3] = { 0.f };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			rotation[i][j] = D3DXVec3Dot(&aabbAxis[i], &obbOrientedAxis[j]);
			absRotation[i][j] = abs(rotation[i][j]) + EPSILON;
		}
	}

	_float3 translation = obbCenter - aabbCenter;
	translation = _float3(D3DXVec3Dot(&translation, &aabbAxis[0]),
						    D3DXVec3Dot(&translation, &aabbAxis[1]),
						    D3DXVec3Dot(&translation, &aabbAxis[2]));

	for (int i = 0; i < 3; ++i)
	{
		ra = pAC->GetHalfSize()[i];
		rb = pOC->GetHalfSize()[0] * absRotation[i][0] +
			 pOC->GetHalfSize()[1] * absRotation[i][1] +
			 pOC->GetHalfSize()[2] * absRotation[i][2];

		if (abs(translation[i]) > ra + rb) return false;
	}

	for (int i = 0; i < 3; ++i)
	{
		ra = pAC->GetHalfSize()[0] * absRotation[0][i] +
			pAC->GetHalfSize()[1] * absRotation[1][i] +
			pAC->GetHalfSize()[2] * absRotation[2][i];
		rb = pOC->GetHalfSize()[i];

		if (abs(translation[0] * rotation[0][i] +
			translation[1] * rotation[1][i] +
			translation[2] * rotation[2][i]) > ra + rb) return false;
	}

	//A0 X B0
	ra = pAC->GetHalfSize()[1] * absRotation[2][0] + pAC->GetHalfSize()[2] * absRotation[1][0];
	rb = pOC->GetHalfSize()[1] * absRotation[0][2] + pOC->GetHalfSize()[2] * absRotation[0][1];
	if (abs(translation[2] * rotation[1][0] - translation[1] * rotation[2][0]) > ra + rb) return false;

	//A0 X B1
	ra = pAC->GetHalfSize()[1] * absRotation[2][1] + pAC->GetHalfSize()[2] * absRotation[1][1];
	rb = pOC->GetHalfSize()[0] * absRotation[0][2] + pOC->GetHalfSize()[2] * absRotation[0][0];
	if (abs(translation[2] * rotation[1][1] - translation[1] * rotation[2][1]) > ra + rb) return false;

	//A0 X B2
	ra = pAC->GetHalfSize()[1] * absRotation[2][2] + pAC->GetHalfSize()[2] * absRotation[1][2];
	rb = pOC->GetHalfSize()[0] * absRotation[0][1] + pOC->GetHalfSize()[1] * absRotation[0][0];
	if (abs(translation[2] * rotation[1][2] - translation[1] * rotation[2][2]) > ra + rb) return false;

	//A1 X B0
	ra = pAC->GetHalfSize()[0] * absRotation[2][0] + pAC->GetHalfSize()[2] * absRotation[0][0];
	rb = pOC->GetHalfSize()[1] * absRotation[1][2] + pOC->GetHalfSize()[2] * absRotation[1][1];
	if (abs(translation[0] * rotation[2][0] - translation[2] * rotation[0][0]) > ra + rb) return false;

	//A1 X B1
	ra = pAC->GetHalfSize()[0] * absRotation[2][1] + pAC->GetHalfSize()[2] * absRotation[0][1];
	rb = pOC->GetHalfSize()[0] * absRotation[1][2] + pOC->GetHalfSize()[2] * absRotation[1][0];
	if (abs(translation[0] * rotation[2][1] - translation[2] * rotation[0][1]) > ra + rb) return false;

	//A1 X B2
	ra = pAC->GetHalfSize()[0] * absRotation[2][2] + pAC->GetHalfSize()[2] * absRotation[0][2];
	rb = pOC->GetHalfSize()[0] * absRotation[1][1] + pOC->GetHalfSize()[1] * absRotation[1][0];
	if (abs(translation[0] * rotation[2][2] - translation[2] * rotation[0][2]) > ra + rb) return false;

	//A2 X B0
	ra = pAC->GetHalfSize()[0] * absRotation[1][0] + pAC->GetHalfSize()[1] * absRotation[0][0];
	rb = pOC->GetHalfSize()[1] * absRotation[2][2] + pOC->GetHalfSize()[2] * absRotation[2][1];
	if (abs(translation[1] * rotation[0][0] - translation[0] * rotation[1][0]) > ra + rb) return false;

	//A2 X B1
	ra = pAC->GetHalfSize()[0] * absRotation[1][1] + pAC->GetHalfSize()[1] * absRotation[0][1];
	rb = pOC->GetHalfSize()[0] * absRotation[2][2] + pOC->GetHalfSize()[2] * absRotation[2][0];
	if (abs(translation[1] * rotation[0][1] - translation[0] * rotation[1][1]) > ra + rb) return false;

	//A2 X B2
	ra = pAC->GetHalfSize()[0] * absRotation[1][2] + pAC->GetHalfSize()[1] * absRotation[0][2];
	rb = pOC->GetHalfSize()[0] * absRotation[2][1] + pOC->GetHalfSize()[1] * absRotation[2][0];
	if (abs(translation[1] * rotation[0][2] - translation[0] * rotation[1][2]) > ra + rb) return false;

	
	CCollisionC* pCC1 = pAC->GetOwner();
	CCollisionC* pCC2 = pOC->GetOwner();

	if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
	{
		pCC1->AddTriggeredCC(pCC2);
		pCC2->AddTriggeredCC(pCC1);
	}
	else
	{
		_float3 normal = obbCenter - aabbCenter;
		_float3 aabbHitPoint = pAC->SurfacePoint(normal);
		_float3 obbHitPoint = pOC->SurfacePoint(-normal);

		_float penet = D3DXVec3Length(&(aabbHitPoint - obbHitPoint));

		pAC->GetOwner()->AddCollisionInfo(_CollisionInfo(pAC, pOC, aabbHitPoint, normal, penet));
		pOC->GetOwner()->AddCollisionInfo(_CollisionInfo(pOC, pAC, obbHitPoint, -normal, penet));
	}
	return true;
}

static bool ObbObb(CCollider* pC1, CCollider* pC2) 
{ 
	CObbCollider* pOC1 = static_cast<CObbCollider*>(pC1);
	CObbCollider* pOC2 = static_cast<CObbCollider*>(pC2);

	SP(CTransformC) spObbTransform1 = pOC1->GetOwner()->GetTransform();
	SP(CTransformC) spObbTransform2 = pOC2->GetOwner()->GetTransform();

	_float3 obb1Center = pOC1->GetOffset() + spObbTransform1->GetPosition();
	_float3 obb2Center = pOC2->GetOffset() + spObbTransform2->GetPosition();

	_float3 obb1OrientedAxis[3];
	obb1OrientedAxis[0] = pOC1->GetRight();
	obb1OrientedAxis[1] = pOC1->GetUp();
	obb1OrientedAxis[2] = pOC1->GetForward();

	_float3 obb2OrientedAxis[3];
	obb2OrientedAxis[0] = pOC2->GetRight();
	obb2OrientedAxis[1] = pOC2->GetUp();
	obb2OrientedAxis[2] = pOC2->GetForward();


	_float	minDiff		= FLT_MAX;
	_float3 minDiffAxis = ZERO_VECTOR;

	_float ra, rb;

	_float rotation[3][3] = { 0.f };
	_float absRotation[3][3] = { 0.f };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			rotation[i][j] = D3DXVec3Dot(&obb1OrientedAxis[i], &obb2OrientedAxis[j]);
			absRotation[i][j] = abs(rotation[i][j]) + EPSILON;
		}
	}

	_float3 translation = obb2Center - obb1Center;
	translation = _float3(D3DXVec3Dot(&translation, &obb1OrientedAxis[0]),
							D3DXVec3Dot(&translation, &obb1OrientedAxis[1]), 
							D3DXVec3Dot(&translation, &obb1OrientedAxis[2]));

	for (int i = 0; i < 3; ++i)
	{
		ra = pOC1->GetHalfSize()[i];
		rb = pOC2->GetHalfSize()[0] * absRotation[i][0] + 
			 pOC2->GetHalfSize()[1] * absRotation[i][1] + 
			 pOC2->GetHalfSize()[2] * absRotation[i][2];

		if (abs(translation[i]) > ra + rb) return false;

		if (minDiff > ra + rb)
		{
			minDiff = ra + rb;
			minDiffAxis = obb1OrientedAxis[i];
		}
	}

	

	for (int i = 0; i < 3; ++i)
	{
		ra = pOC1->GetHalfSize()[0] * absRotation[0][i] + 
			 pOC1->GetHalfSize()[1] * absRotation[1][i] + 
			 pOC1->GetHalfSize()[2] * absRotation[2][i];
		rb = pOC2->GetHalfSize()[i];

		if (abs(translation[0] * rotation[0][i] +
				translation[1] * rotation[1][i] +
				translation[2] * rotation[2][i]) > ra + rb) return false;

		if (minDiff > ra + rb)
		{
			minDiff = ra + rb;
			minDiffAxis = obb2OrientedAxis[i];
		}
	}

	//A0 X B0
	ra = pOC1->GetHalfSize()[1] * absRotation[2][0] + pOC1->GetHalfSize()[2] * absRotation[1][0];
	rb = pOC2->GetHalfSize()[1] * absRotation[0][2] + pOC2->GetHalfSize()[2] * absRotation[0][1];
	if (abs(translation[2] * rotation[1][0] - translation[1] * rotation[2][0]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff	= ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[0], &obb2OrientedAxis[0]);
	}

	//A0 X B1
	ra = pOC1->GetHalfSize()[1] * absRotation[2][1] + pOC1->GetHalfSize()[2] * absRotation[1][1];
	rb = pOC2->GetHalfSize()[0] * absRotation[0][2] + pOC2->GetHalfSize()[2] * absRotation[0][0];
	if (abs(translation[2] * rotation[1][1] - translation[1] * rotation[2][1]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[0], &obb2OrientedAxis[1]);
	}

	//A0 X B2
	ra = pOC1->GetHalfSize()[1] * absRotation[2][2] + pOC1->GetHalfSize()[2] * absRotation[1][2];
	rb = pOC2->GetHalfSize()[0] * absRotation[0][1] + pOC2->GetHalfSize()[1] * absRotation[0][0];
	if (abs(translation[2] * rotation[1][2] - translation[1] * rotation[2][2]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[0], &obb2OrientedAxis[2]);
	}

	//A1 X B0
	ra = pOC1->GetHalfSize()[0] * absRotation[2][0] + pOC1->GetHalfSize()[2] * absRotation[0][0];
	rb = pOC2->GetHalfSize()[1] * absRotation[1][2] + pOC2->GetHalfSize()[2] * absRotation[1][1];
	if (abs(translation[0] * rotation[2][0] - translation[2] * rotation[0][0]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[1], &obb2OrientedAxis[0]);
	}

	//A1 X B1
	ra = pOC1->GetHalfSize()[0] * absRotation[2][1] + pOC1->GetHalfSize()[2] * absRotation[0][1];
	rb = pOC2->GetHalfSize()[0] * absRotation[1][2] + pOC2->GetHalfSize()[2] * absRotation[1][0];
	if (abs(translation[0] * rotation[2][1] - translation[2] * rotation[0][1]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[1], &obb2OrientedAxis[1]);
	}

	//A1 X B2
	ra = pOC1->GetHalfSize()[0] * absRotation[2][2] + pOC1->GetHalfSize()[2] * absRotation[0][2];
	rb = pOC2->GetHalfSize()[0] * absRotation[1][1] + pOC2->GetHalfSize()[1] * absRotation[1][0];
	if (abs(translation[0] * rotation[2][2] - translation[2] * rotation[0][2]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[1], &obb2OrientedAxis[2]);
	}

	//A2 X B0
	ra = pOC1->GetHalfSize()[0] * absRotation[1][0] + pOC1->GetHalfSize()[1] * absRotation[0][0];
	rb = pOC2->GetHalfSize()[1] * absRotation[2][2] + pOC2->GetHalfSize()[2] * absRotation[2][1];
	if (abs(translation[1] * rotation[0][0] - translation[0] * rotation[1][0]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[2], &obb2OrientedAxis[0]);
	}

	//A2 X B1
	ra = pOC1->GetHalfSize()[0] * absRotation[1][1] + pOC1->GetHalfSize()[1] * absRotation[0][1];
	rb = pOC2->GetHalfSize()[0] * absRotation[2][2] + pOC2->GetHalfSize()[2] * absRotation[2][0];
	if (abs(translation[1] * rotation[0][1] - translation[0] * rotation[1][1]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[2], &obb2OrientedAxis[1]);
	}

	//A2 X B2
	ra = pOC1->GetHalfSize()[0] * absRotation[1][2] + pOC1->GetHalfSize()[1] * absRotation[0][2];
	rb = pOC2->GetHalfSize()[0] * absRotation[2][1] + pOC2->GetHalfSize()[1] * absRotation[2][0];
	if (abs(translation[1] * rotation[0][2] - translation[0] * rotation[1][2]) > ra + rb) return false;

	if (minDiff > ra + rb)
	{
		minDiff = ra + rb;
		D3DXVec3Cross(&minDiffAxis, &obb1OrientedAxis[2], &obb2OrientedAxis[2]);
	}


	CCollisionC* pCC1 = pOC1->GetOwner();
	CCollisionC* pCC2 = pOC2->GetOwner();

	if (pCC1->GetIsTrigger() || pCC2->GetIsTrigger())
	{
		pCC1->AddTriggeredCC(pCC2);
		pCC2->AddTriggeredCC(pCC1);
	}
	else
	{
		_float3 closestFromObb1 = pOC1->ClosestFromPoint(obb2Center);
		_float3 closestFromObb2 = pOC2->ClosestFromPoint(obb1Center);

		GET_CUR_SCENE->GetLayers()[8]->GetGameObjects()[0]->GetTransform()->SetPosition(closestFromObb1);
		GET_CUR_SCENE->GetLayers()[8]->GetGameObjects()[1]->GetTransform()->SetPosition(closestFromObb2);

		_float3 normal = obb2Center - obb1Center;
		_float3 obb1HitPoint = pOC1->SurfacePoint(normal);
		_float3 obb2HitPoint = pOC2->SurfacePoint(-normal);

		_float penet = D3DXVec3Length(&(obb1HitPoint - obb2HitPoint));

		pOC1->GetOwner()->AddCollisionInfo(_CollisionInfo(pOC1, pOC2, obb1HitPoint, normal, penet));
		pOC2->GetOwner()->AddCollisionInfo(_CollisionInfo(pOC2, pOC1, obb2HitPoint, -normal, penet));
	}
	return true; 
}

END
END

#endif
