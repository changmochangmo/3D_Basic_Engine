#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H


BEGIN(Engine)
class CCollider;
class ENGINE_DLL CCollisionC final : public CComponent
{
public:
	explicit CCollisionC(void);
	 ~CCollisionC(void);
public:
				SP(CComponent) MakeClone(CGameObject* pObject) override;

				void Awake();
				void Start(SP(CComponent) spThis) override;

				void FixedUpdate(SP(CComponent) spThis) override;
				void Update(SP(CComponent) spThis) override;
				void LateUpdate(SP(CComponent) spThis) override;

				void OnDestroy(void) override;

				void OnEnable(void) override;
				void OnDisable(void) override;

				CCollisionC* AddCollider(CCollider* collider);

private:
				void				CalculateBS				(void);
				void				MergingTwoBS			(_float3 curOffset, _float curRadius);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Collider;

protected:
	typedef std::vector<CCollider*> _COLLIDERS;
	GETTOR			(_COLLIDERS,					m_vColliders,	{},				Colliders)
	GETTOR_SETTOR	(_int,							m_colliderID,	0,				ColliderID)
	
	GETTOR			(_float3,						m_offsetBS,		ZERO_VECTOR,	OffsetBS)
	GETTOR			(_float,						m_radiusBS,		0,				RadiusBS)

	GETTOR			(SP(CTransformC),	m_pTransform,	nullptr,		Transform)
};
END

#endif // COLLIDERCOMPONENT_H