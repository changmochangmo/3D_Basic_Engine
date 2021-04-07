#ifndef  RIGIDBODYCOMPONENT_H
#define  RIGIDBODYCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CRigidBodyC final : public CComponent
{
public:
	explicit	CRigidBodyC(void);
	~CRigidBodyC(void);

public:
		 SP(CComponent) MakeClone(CGameObject * pObject) override;

		 void Awake();
		 void Start(SP(CComponent) spThis) override;

		 void FixedUpdate(SP(CComponent) spThis) override;
		 void Update(SP(CComponent) spThis) override;
		 void LateUpdate(SP(CComponent) spThis) override;

		 void OnDestroy(void) override;

		 void OnEnable(void) override;
		 void OnDisable(void) override;

	
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
	CTransformC* m_pTransform;

};

END
#endif // ! RIGIDBODYCOMPONENT_H
