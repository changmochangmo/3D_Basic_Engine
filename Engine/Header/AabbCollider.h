#ifndef AABBCOLLIDER_H
#define AABBCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CAabbCollider final : public CCollider
{
private:
	explicit		CAabbCollider		(void);
	virtual		   ~CAabbCollider		(void);

public:
	static		CAabbCollider*		Create				(_float3 size, _float3 offset = _float3(0, 0, 0));
				CCollider*			MakeClone			(CColliderComponent* pCC) override;

				void				Awake				(void) override;
				void				OnDestroy			(void) override;

				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

				_float				SqDistFromPoint		(_float3 point);
				_float3				ClosestFromPoint	(_float3 point);

private:
				void				MakeBS				(void) override;

protected:
	GETTOR_SETTOR	(_float3,		m_offset,		ZERO_VECTOR,	Offset)
	GETTOR_SETTOR	(_float3,		m_halfSize,		ONE_VECTOR,		HalfSize)
	GETTOR_SETTOR	(_float3,		m_size,			ONE_VECTOR,		Size)
};
END
#endif