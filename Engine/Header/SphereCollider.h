#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CSphereCollider final : public CCollider
{
private:
	explicit						CSphereCollider		(void);
								   ~CSphereCollider		(void);
public:
	static			CSphereCollider*	Create		(_float radius = 1,
													 _float3 offset = _float3(0, 0, 0));

					CCollider*			MakeClone	(CColliderComponent* pCC) override;
					
					void				Awake		(void) override;
					void				OnDestroy	(void) override;
														   
					void				OnEnable	(void) override;
					void				OnDisable	(void) override;

private:
					void				MakeBS		(void) override;
protected:
	GETTOR_SETTOR	(_float,		m_radius,			0.f,			Radius)
	GETTOR_SETTOR	(_float3,		m_offset,			ZERO_VECTOR,	Offset)
};
END

#endif // SPHERECOLLIDER_H