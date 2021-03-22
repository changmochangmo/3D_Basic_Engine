#ifndef  CColliderManager_H
#define  CColliderManager_H

#include "Engine.h"

BEGIN(Engine)
class CColliderComponent;
class CBoxCollider;
class CSphereCollider;
class CRayCollider;
class ENGINE_DLL CColliderManager final : public CEngine
{
	DECLARE_SINGLETON(CColliderManager)
public:
	void				Awake					(void) override;
	void				Start					(_int numOfColliderID);

	_uint				FixedUpdate				(void);
	_uint				Update					(void);
	_uint				LateUpdate				(void);

	void				OnDestroy				(void);

	void				OnEnable				(void);
	void				OnDisable				(void);

	void				AddColliderToManager	(SHARED(CColliderComponent) vecObject);

	bool				OnColliderEnter			(SHARED(CColliderComponent) pColliderComponent, 
												 std::vector<CGameObject*>& returnCollider/*,
												 _int colliderID*/);

	std::vector<_int>&	GetLayersToCheck		(_int colliderID);

private:
	void				InitCollisionChecker	(void);
	void				InitCollisionMap		(void);
	
private:
	std::vector<std::vector<_int>> m_vCollisionMap;
	std::vector<std::vector<SHARED(CColliderComponent)>> m_vColliderComponents;

	typedef std::function<_bool(CCollider*, CCollider*)>	_COLLISION_CHECKER;
	typedef std::array<std::array <_COLLISION_CHECKER, (_int)EColliderType::NumOfCT>, (_int)EColliderType::NumOfCT> _COLLISION_CHECKER_2D;
	_COLLISION_CHECKER_2D m_fpCollisionChecker;

	GETTOR	(_int,	m_numOfColliderID, 0, NumOfColliderID)
};

END
#endif // ! CColliderManager_H