#ifndef COLLIDER_H
#define COLLIDER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CCollider abstract : public CEngine
{
public:
	explicit								CCollider		(void);
	virtual								   ~CCollider		(void);

public:
	virtual			CCollider*				MakeClone		(CColliderComponent* pCC) PURE;

	virtual			void					Awake			(void) PURE;
	virtual			void					OnDestroy		(void) PURE;

	virtual			void					OnEnable		(void) PURE;
	virtual			void					OnDisable		(void) PURE;

protected:
	virtual			void					MakeBS			(void) PURE;
protected:
	GETTOR_SETTOR	(_int,					m_colliderType,		-1,			ColliderType)
	GETTOR_SETTOR	(CColliderComponent*,	m_pOwner,			nullptr,	Owner)

	GETTOR_SETTOR	(_float3,				m_offsetBS,			FLOAT3_ZERO,	OffsetBS)
	GETTOR_SETTOR	(_float,				m_radiusBS,			0,				RadiusBS)

};

END

#endif // COLLIDER_H