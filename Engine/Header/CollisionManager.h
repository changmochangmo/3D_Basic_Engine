#ifndef  CCOLLISIONMANAGER_H
#define  CCOLLISIONMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CCollisionC;
class CBoxCollider;
class CSphereCollider;
class CRayCollider;
class ENGINE_DLL CCollisionManager final : public CEngine
{
	DECLARE_SINGLETON(CCollisionManager)
public:
	void				Awake					(void) override;
	void				Start					(_int numOfColliderID);

	void				FixedUpdate				(void);
	void				Update					(void);
	void				LateUpdate				(void);

	void				OnDestroy				(void);

	void				OnEnable				(void);
	void				OnDisable				(void);

	void				AddCollisionToManager	(SP(CCollisionC) vecObject);

	std::vector<_int>&	GetLayersToCheck		(_int colliderID);

private:
	void				InitCollisionChecker	(void);
	void				InitCollisionMap		(void);

	void				CheckCollision			(CCollisionC* pCC);
	
private:
	std::vector<std::vector<_int>> m_vCollisionMap;
	std::vector<std::vector<SP(CCollisionC)>> m_vCollisionComponents;

	typedef std::function<_bool(CCollider*, CCollider*)>	_COLLISION_CHECKER;
	typedef std::array<std::array <_COLLISION_CHECKER, (_int)EColliderType::NumOfCT>, (_int)EColliderType::NumOfCT> _COLLISION_CHECKER_2D;
	_COLLISION_CHECKER_2D m_fpCollisionChecker;

	GETTOR	(_int,	m_numOfColliderID, 0, NumOfColliderID)
};

END
#endif // ! CColliderManager_H