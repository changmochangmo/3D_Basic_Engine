#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H


BEGIN(Engine)
class CCollider;
class ENGINE_DLL CCollisionC final : public CComponent
{
	friend class CCollisionManager;
public:
	explicit						CCollisionC			(void);
								   ~CCollisionC			(void);
//Engine
public:
					SP(CComponent)	MakeClone			(CObject* pObject) override;

					void			Awake				(void);
					void			Start				(SP(CComponent) spThis) override;

					void			FixedUpdate			(SP(CComponent) spThis) override;
					void			Update				(SP(CComponent) spThis) override;
					void			LateUpdate			(SP(CComponent) spThis) override;

					void			OnDestroy			(void) override;

					void			OnEnable			(void) override;
					void			OnDisable			(void) override;

//interface			
public:
					void			AddCollider			(CCollider* pCollider);

					void			AddCollisionInfo	(_CollisionInfo collisionInfo);

					void			AddTriggeredCC		(CCollisionC* pCC);
private:
					void			AddColliderFromFile	(void);
					void			MergingBS			(CCollider* pCollider);

					void			ProcessCollisions	(void);
					void			ProcessTriggers		(void);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Collision;

protected:
	typedef std::vector<_CollisionInfo> _COLLISIONS;
	typedef	std::vector<CCollisionC*> _TRIGGERS;
	typedef std::vector<CCollider*> _COLLIDERS;
	GETTOR			(_COLLISIONS,		m_vCurCollisions,	{},				CurCollisions)
	GETTOR			(_COLLISIONS,		m_vPreCollisions,	{},				PreCollisions)

	GETTOR			(_TRIGGERS,			m_vCurTriggers,		{},				CurTriggers)
	GETTOR			(_TRIGGERS,			m_vPreTriggers,		{},				PreTriggers)

	GETTOR			(_COLLIDERS,		m_vColliders,		{},				Colliders)
	GETTOR_SETTOR	(_int,				m_collisionID,		UNDEFINED,		CollisionID)

	GETTOR_SETTOR	(_bool,				m_isTrigger,		false,			IsTrigger)
	
	GETTOR_SETTOR	(_float3,			m_offsetBS,			ZERO_VECTOR,	OffsetBS)
	GETTOR_SETTOR	(_float,			m_radiusBS,			UNDEFINED,		RadiusBS)

	GETTOR			(SP(CTransformC),	m_spTransform,		nullptr,		Transform)
	GETTOR			(SP(CRigidBodyC),	m_spRigidbody,		nullptr,		Rigidbody)
	
	GETTOR_SETTOR	(_bool,				m_resolveIn,		true,			ResolveIn)

	
};
END

#endif // COLLIDERCOMPONENT_H