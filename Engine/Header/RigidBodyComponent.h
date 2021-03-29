#ifndef  RIGIDBODYCOMPONENT_H
#define  RIGIDBODYCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CRigidBodyComponent : public CComponent
{
public:
	explicit	CRigidBodyComponent(void);
	~CRigidBodyComponent(void);

public:
	virtual SHARED(CComponent) MakeClone(CGameObject * pObject) override;

	virtual void Awake();
	virtual void Start(SHARED(CComponent) spThis) override;

	virtual _uint FixedUpdate(SHARED(CComponent) spThis) override;
	virtual _uint Update(SHARED(CComponent) spThis) override;
	virtual _uint LateUpdate(SHARED(CComponent) spThis) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;

	
	void GravityDrag(_float3& velocity);

	void AddForce(_float3 force);
	void SetForce(_float3 force);
	void TranslateForce(_float3 force);
private:
	void ElasticCollision(std::vector<CGameObject*>& obj);
	void DecelerationFunction(std::vector<CGameObject*>& col);

public:
	static const	EComponentID		m_s_componentID = EComponentID::RigidBody;

protected:
	GETTOR_SETTOR(_float, m_mass, 1, Mass)
	GETTOR_SETTOR(_float, m_bounciness, 0, Bounciness) 
	GETTOR_SETTOR(_float, m_drag, 1, Drag) 
	GETTOR_SETTOR(_bool, m_useGravity, true, UseGravity)
	GETTOR_SETTOR(_BOOL3, m_freezePosition, _BOOL3(false, false, false), FreezePosition) 
	GETTOR_SETTOR(_BOOL3, m_freezeRotation, _BOOL3(false, false, false), FreezeRotation) 
	GETTOR_SETTOR(_bool, m_groundCheck, false, GroundCheck)
	GETTOR_SETTOR(_float3, m_velocity, GRAVITY, Velocity) 
	GETTOR_SETTOR(_float3, m_netForce, ZERO_VECTOR, NetForce)

	_float m_damping = 2.999f;	
	_float3 m_separatingVelocity; 
	CTransformComponent* m_pTransform;

};

END
#endif // ! RIGIDBODYCOMPONENT_H
