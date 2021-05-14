#include "EngineStdafx.h"
#include "Object.h"
#include "CollisionManager.h"
#include "FRC.h"

USING(Engine)
CRigidBodyC::CRigidBodyC(void)
{
}

CRigidBodyC::~CRigidBodyC(void)
{
	OnDestroy();
}

SP(CComponent) CRigidBodyC::MakeClone(CObject * pObject)
{
	SP(CRigidBodyC) spClone(new CRigidBodyC);
	InitClone(spClone, pObject);
	__super::InitClone(spClone, pObject);

	
	spClone->SetMass(m_mass);
	spClone->SetDrag(m_drag);
	spClone->SetUseGravity(m_useGravity);
	spClone->m_velocity = m_velocity;

	return spClone;
}

void CRigidBodyC::Awake()
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
}

void CRigidBodyC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_spTransform = m_pOwner->GetComponent<CTransformC>();
}

void CRigidBodyC::FixedUpdate(SP(CComponent) spThis)
{
}

void CRigidBodyC::Update(SP(CComponent) spThis)
{
}

void CRigidBodyC::LateUpdate(SP(CComponent) spThis)
{
	UpdateLinear();
	//아직 미구현
	UpdateAngular();
}

void CRigidBodyC::OnDestroy(void)
{
}

void CRigidBodyC::OnEnable(void)
{
}

void CRigidBodyC::OnDisable(void)
{
}

#pragma region SettorAdder
void CRigidBodyC::AddForce(_float3 force)
{
	m_force += force;
}

void CRigidBodyC::AddForceX(_float adder)
{
	m_force.x += adder;
}

void CRigidBodyC::AddForceY(_float adder)
{
	m_force.y += adder;
}

void CRigidBodyC::AddForceZ(_float adder)
{
	m_force.z += adder;
}

void CRigidBodyC::AddTorque(_float3 torque)
{
	m_torque += torque;
}
void CRigidBodyC::SetVelocityY(_float num)
{
	m_velocity.y = num;
}
#pragma endregion

void CRigidBodyC::UpdateLinear(void)
{
	_float deltaTime = GET_DT;

	if (m_useGravity)
		AddForce(GRAVITY * m_mass);

	m_force *= (1 - m_drag);

	m_velocity += (m_force / m_mass) * deltaTime;
	m_spTransform->AddPosition(m_velocity * deltaTime);

	m_force = ZERO_VECTOR;
}

void CRigidBodyC::UpdateAngular(void)
{
}