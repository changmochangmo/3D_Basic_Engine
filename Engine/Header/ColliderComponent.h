#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H


BEGIN(Engine)
class CCollider;
class ENGINE_DLL CColliderComponent final : public CComponent
{
public:
	explicit CColliderComponent(void);
	 ~CColliderComponent(void);
public:
	virtual SHARED(CComponent) MakeClone(CGameObject* pObject) override;

	virtual void Awake();
	virtual void Start(SHARED(CComponent) spThis) override;

	virtual _uint FixedUpdate(SHARED(CComponent) spThis) override;
	virtual _uint Update(SHARED(CComponent) spThis) override;
	virtual _uint LateUpdate(SHARED(CComponent) spThis) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;

	CColliderComponent* AddCollider(CCollider* collider);

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

	GETTOR			(SHARED(CTransformComponent),	m_pTransform,	nullptr,		Transform)
};
END

#endif // COLLIDERCOMPONENT_H