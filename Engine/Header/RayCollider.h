#ifndef RAYCOLLIDER_H
#define RAYCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CRayCollider final : public CCollider
{
private:
	explicit						CRayCollider		(void);
								   ~CRayCollider		(void);
public:
	static			CRayCollider*		Create				(_float3 offset, _float3 direction);
					CCollider*			MakeClone			(CColliderComponent* pCC) override;

					void				Awake				(void) override;
					void				OnDestroy			(void) override;
																   
					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

private:
					void				MakeBS				(void) override;
					//_float				SqDistFromPoint		(_float3 point);
					//_float3				ClosestFromPoint	(_float3 point);
protected:
	GETTOR_SETTOR	(_float3,			m_offset,			FLOAT3_ZERO,		Offset)
	GETTOR_SETTOR	(_float3,			m_direction,		FLOAT3_ZERO,		Direction)
	GETTOR_SETTOR	(_float,			m_size,				FLT_MAX,			Size)
};
END
#endif