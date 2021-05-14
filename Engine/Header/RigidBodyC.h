#ifndef  RIGIDBODYCOMPONENT_H
#define  RIGIDBODYCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CRigidBodyC final : public CComponent
{
public:
	explicit						CRigidBodyC		(void);
								   ~CRigidBodyC		(void);

public:
				SP(CComponent)		MakeClone		(CObject * pObject) override;
				
				void				Awake			(void) override;
				void				Start			(SP(CComponent) spThis) override;

				void				FixedUpdate		(SP(CComponent) spThis) override;
				void				Update			(SP(CComponent) spThis) override;
				void				LateUpdate		(SP(CComponent) spThis) override;

				void				OnDestroy		(void) override;

				void				OnEnable		(void) override;
				void				OnDisable		(void) override;

public:
				void				AddForce		(_float3 force);
				void				AddForceX		(_float adder);
				void				AddForceY		(_float adder);
				void				AddForceZ		(_float adder);

				void				AddTorque		(_float3 torque);

				void				SetVelocityY	(_float num);
private:
				void				UpdateLinear	(void);
				void				UpdateAngular	(void);

public:
	static const	EComponentID		m_s_componentID = EComponentID::RigidBody;

private:
	//이 아래는 아직 뭔지 몰라서 못넣음
	//intertiaTensor
	//intertiaTensorRotation
	//interpolation (보간)
	//sleepThreshold //끄는 기준인거 같음.
	//solverIterationCount
	//useConeFriction 원추마찰력 사용 유무
	//여기부터 계속~
	
	GETTOR_SETTOR	(_bool,				m_useGravity,			true,				UseGravity)
	GETTOR_SETTOR	(_bool,				m_detectCollision,		true,				DetectCollision)
	//0일 경우 무한대.
	GETTOR_SETTOR	(_float,			m_mass,					1.f,				Mass)
	GETTOR_SETTOR	(_float3,			m_centerOfMass,			ZERO_VECTOR,		CenterOfMass)
	GETTOR_SETTOR	(_float3,			m_worldCenterOfMass,	ZERO_VECTOR,		WorldCenterOfMass)

	GETTOR_SETTOR	(_float3,			m_force,				ZERO_VECTOR,		Force)
	GETTOR_SETTOR	(_float3,			m_torque,				ZERO_VECTOR,		Torque)

	GETTOR_SETTOR	(_float,			m_drag,					0.f,				Drag)
	GETTOR_SETTOR	(_float,			m_angularDrag,			0.f,				AngularDrag)

	GETTOR			(_float3,			m_velocity,				ZERO_VECTOR,		Velocity)
	GETTOR_SETTOR	(_float3,			m_angularVelocity,		ZERO_VECTOR,		AngularVelocity)

	GETTOR_SETTOR	(_float,			m_maxVelocity,			UNDEFINED,			MaxVelocity)
	GETTOR_SETTOR	(_float,			m_maxAngularVelocity,	UNDEFINED,			MaxAngularVelocity)

	GETTOR_SETTOR	(EConstraint,		m_constraint,			EConstraint::None,	Constraint)
	GETTOR			(SP(CTransformC),	m_spTransform,			nullptr,			Transform)

};

END
#endif // ! RIGIDBODYCOMPONENT_H
