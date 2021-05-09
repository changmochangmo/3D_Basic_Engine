#ifndef COLLIDER_H
#define COLLIDER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CCollider abstract
{
protected:
	explicit						CCollider			(void);
	virtual						   ~CCollider			(void);

public:
					void			Free				(void);
	virtual			CCollider*		MakeClone			(CCollisionC* pCC) PURE;

	virtual			void			Awake				(void) PURE;
	virtual			void			OnDestroy			(void) PURE;

	virtual			void			OnEnable			(void) PURE;
	virtual			void			OnDisable			(void) PURE;

//Interface
public:
	virtual			void			UpdatePosition		(void) PURE;

protected:
	virtual			void			MakeBS				(void) PURE;
protected:
	GETTOR_SETTOR	(_int,			m_colliderType,		-1,				ColliderType)
	GETTOR_SETTOR	(CCollisionC*,	m_pOwner,			nullptr,		Owner)

	//부모 상대좌표
	GETTOR_SETTOR	(_float3,		m_offsetOrigin,		ZERO_VECTOR,	OffsetOrigin)
	//실제 좌표
	GETTOR_SETTOR	(_float3,		m_offset,			ZERO_VECTOR,	Offset)
	//BoundingSphere의 반지름.
	GETTOR_SETTOR	(_float,		m_radiusBS,			0,				RadiusBS)	
};

END

#endif // COLLIDER_H