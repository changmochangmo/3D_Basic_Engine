#ifndef OBBCOLLIDER_H
#define OBBCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CObbCollider final : public CCollider
{
private:
	explicit		CObbCollider		(void);
	virtual		   ~CObbCollider		(void);

public:
	static		CObbCollider*		Create				(_float3 size, _float3 offset);
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

	GETTOR_SETTOR	(_float3,		m_orientedX,	_float3(1, 0, 0), OrientedX)
	GETTOR_SETTOR	(_float3,		m_orientedY,	_float3(0, 1, 0), OrientedY)
	GETTOR_SETTOR	(_float3,		m_orientedZ,	_float3(0, 0, 1), OrientedZ)
};
END
#endif