#ifndef OBBCOLLIDER_H
#define OBBCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CObbCollider final : public CCollider
{
private:
	explicit						CObbCollider		(void);
	virtual						   ~CObbCollider		(void);

public:
	static			CObbCollider*	Create				(_float3 size, _float3 offset, 
														 _float3 right, _float3 up, _float3 forward);
					CCollider*		MakeClone			(CCollisionC* pCC) override;

					void			Awake				(void) override;
					void			OnDestroy			(void) override;

					void			OnEnable			(void) override;
					void			OnDisable			(void) override;

					_float			SqDistFromPoint		(_float3 const& point);
					_float3			ClosestFromPoint	(_float3 const& point);
					_float3			SurfacePoint		(_float3 const& dir);
private:
					void			MakeBS				(void) override;
protected:
	GETTOR_SETTOR	(_float3,		m_halfSize,			ONE_VECTOR,			HalfSize)
	GETTOR_SETTOR	(_float3,		m_size,				ONE_VECTOR,			Size)

	GETTOR_SETTOR	(_float3,		m_right,			RIGHT_VECTOR,		Right)
	GETTOR_SETTOR	(_float3,		m_up,				UP_VECTOR,			Up)
	GETTOR_SETTOR	(_float3,		m_forward,			FORWARD_VECTOR,		Forward)
};
END
#endif