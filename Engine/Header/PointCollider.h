#ifndef POINTCOLLIDER_H
#define POINTCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CPointCollider final : public CCollider
{
private:
	explicit						CPointCollider		(void);
	virtual						   ~CPointCollider		(void);

public:
	static		CPointCollider*		Create			(_float3 offset);
				CCollider*			MakeClone		(CCollisionC* pCC) override;

				void				Awake			(void) override;
				void				OnDestroy		(void) override;

				void				OnEnable		(void) override;
				void				OnDisable		(void) override;

				void				UpdatePosition	(void) override;
private:
				void				MakeBS			(void) override;

};
END
#endif