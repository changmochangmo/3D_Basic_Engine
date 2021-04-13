#include "EngineStdafx.h"
#include "GameObject.h"
#include "ColliderManager.h"
#include "FRC.h"

USING(Engine)
CRigidBodyC::CRigidBodyC(void)
{
}

CRigidBodyC::~CRigidBodyC(void)
{
	OnDestroy();
}

SP(CComponent) CRigidBodyC::MakeClone(CGameObject * pObject)
{
	SP(CRigidBodyC) spClone(new CRigidBodyC);
	InitClone(spClone, pObject);
	__super::InitClone(spClone, pObject);

	spClone->SetMass(m_mass);
	spClone->SetDrag(m_drag);
	spClone->SetUseGravity(m_useGravity);
	spClone->SetVelocity(m_velocity);

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
	UpdateLinear();

	//아직 미구현
	UpdateAngular();
	
	_float deltaTime = GET_DT;

	_float3 nextFramePos = m_spTransform->GetPosition() + m_velocity * deltaTime;
	//_float3 nextFrameRot = m_rotation + m_angularVelocity * deltaTime;

	//CColliderManager::GetInstance()->CheckCollision()
}

void CRigidBodyC::Update(SP(CComponent) spThis)
{
}

void CRigidBodyC::LateUpdate(SP(CComponent) spThis)
{
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
	m_force.x += adder;
}

void CRigidBodyC::AddForceZ(_float adder)
{
	m_force.y += adder;
}

void CRigidBodyC::AddTorque(_float3 torque)
{
	m_torque += torque;
}
#pragma endregion

void CRigidBodyC::UpdateLinear(void)
{
	_float deltaTime = GET_DT;

	if (m_useGravity)
		AddForce(GRAVITY * m_mass);

	m_force *= (1 - m_drag);

	m_velocity += (m_force / m_mass) * deltaTime;
}

void CRigidBodyC::UpdateAngular(void)
{
}