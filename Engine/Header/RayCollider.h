#ifndef RAYCOLLIDER_H
#define RAYCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CRayCollider final : public CCollider
{
private:
	explicit							CRayCollider		(void);
									   ~CRayCollider		(void);
public:
	static			CRayCollider*		Create				(_float3 offset, _float3 direction, 
															 _float length, ERayType rayType = ERayType::LIMITED);
					CCollider*			MakeClone			(CCollisionC* pCC) override;

					void				Awake				(void) override;
					void				OnDestroy			(void) override;
																   
					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

					void				UpdatePosition		(void) override;

private:
					void				MakeBS				(void) override;
protected:
	GETTOR_SETTOR	(_float3,			m_directionOrigin,	ZERO_VECTOR,		DirectionOrigin)
	GETTOR_SETTOR	(_float3,			m_direction,		ZERO_VECTOR,		Direction)
	GETTOR_SETTOR	(_float,			m_length,			0,					Length)
	GETTOR_SETTOR	(ERayType,			m_rayType,			ERayType::LIMITED,	RayType)

	GETTOR_SETTOR	(CObject*,			m_pTarget,			nullptr,			Target)
};
END
#endif