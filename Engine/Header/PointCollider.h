#ifndef POINTCOLLIDER_H
#define POINTCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CPointCollider final : public CCollider
{
private:
	explicit			CPointCollider		(void);
	virtual			   ~CPointCollider		(void);

public:
	static		CPointCollider*		Create		(_float3 offset);
				CCollider*			MakeClone	(CColliderComponent* pCC) override;

				void				Awake		(void) override;
				void				OnDestroy	(void) override;

				void				OnEnable	(void) override;
				void				OnDisable	(void) override;

private:
				void				MakeBS		(void) override;

protected:
	GETTOR_SETTOR	(_float3,		m_offset,		FLOAT3_ZERO,	Offset)
};
END
#endif