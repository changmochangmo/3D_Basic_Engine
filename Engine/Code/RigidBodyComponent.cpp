#include "EngineStdafx.h"
#include "GameObject.h"
#include "ColliderManager.h"

USING(Engine)
CRigidBodyComponent::CRigidBodyComponent(void)
{
}

CRigidBodyComponent::~CRigidBodyComponent(void)
{
}

SHARED(CComponent) CRigidBodyComponent::MakeClone(CGameObject * pObject)
{
	SHARED(CRigidBodyComponent) pClone(new CRigidBodyComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetMass(m_mass);
	pClone->SetDrag(m_drag);
	pClone->SetUseGravity(m_useGravity);
	pClone->SetFreezePosition(m_freezePosition);
	pClone->SetFreezeRotation(m_freezeRotation);
	pClone->SetGroundCheck(m_groundCheck);
	pClone->SetVelocity(m_velocity);
	pClone->SetBounciness(m_bounciness);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CRigidBodyComponent::Awake()
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
}

void CRigidBodyComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_pTransform = m_pOwner->GetComponent<CTransformComponent>().get();
	m_mass = MathfMin(m_mass, 100);
	m_mass /= 100;
	m_bounciness = MathfMin(m_bounciness, 1);
	m_separatingVelocity = FLOAT3_ZERO;
}

_uint CRigidBodyComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	std::vector<CGameObject*> col;
	SHARED(CColliderComponent) spCC = m_pOwner->GetComponent<CColliderComponent>();

	bool crushCheck = false;
	if (spCC->GetIsStarted())
		crushCheck = CColliderManager::GetInstance()->OnColliderEnter(spCC, col);


	if (crushCheck)
	{
		DecelerationFunction(col);
  
		ElasticCollision(col);
		
		m_pTransform->SetPosition(m_pTransform->GetPosition() + (GET_DT * m_velocity));
	}
	else if (!crushCheck || !m_groundCheck)
	{
		GravityDrag(m_velocity);

		m_separatingVelocity = m_pTransform->GetPosition();
		m_pTransform->SetPosition(m_pTransform->GetPosition() + (GET_DT * m_velocity));
		m_separatingVelocity = m_pTransform->GetPosition() - m_separatingVelocity;
	}

	m_netForce = FLOAT3_ZERO;
	return _uint();
}

_uint CRigidBodyComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CRigidBodyComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CRigidBodyComponent::OnDestroy(void)
{
}

void CRigidBodyComponent::OnEnable(void)
{
}

void CRigidBodyComponent::OnDisable(void)
{
}

void CRigidBodyComponent::GravityDrag(_float3 & velocity)
{
	_float3 drag = velocity;
	D3DXVec3Normalize(&drag, &drag);

	velocity.y += GRAVITY.y * GET_DT;

	/*drag.y = -drag.y * ((1 - drag.y) + (10 * (drag.y * drag.y)));
	velocity.y -= drag.y;*/
}

void CRigidBodyComponent::AddForce(_float3 force)
{
	m_netForce += force;

	_float xForce = (force.x / abs(m_mass));
	_float yForce = (force.y / abs(m_mass));
	_float zForce = (force.z / abs(m_mass));

	// F = ma 
	// a = F / m

	_float3 a = _float3(xForce, yForce, zForce);
	m_velocity += a;

	if (m_velocity.y != 0)
		m_groundCheck = false;

	m_pTransform->SetPosition(m_pTransform->GetPosition() + (GET_DT * m_velocity));
}

void CRigidBodyComponent::SetForce(_float3 force)
{
	_float xForce = (force.x / m_mass);
	_float yForce = (force.y / m_mass);
	_float zForce = (force.z / m_mass);

	_float3 a = _float3(xForce, yForce, zForce);
	m_velocity = a;

	if (m_velocity.y != 0)
		m_groundCheck = false;

	m_pTransform->SetPosition(m_pTransform->GetPosition() + (GET_DT * m_velocity));
}

void CRigidBodyComponent::TranslateForce(_float3 force)
{
	_float xForce = (force.x / m_mass);
	_float yForce = (force.y / m_mass);
	_float zForce = (force.z / m_mass);

	_float3 a = _float3(xForce, yForce, zForce);

	_mat rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_pTransform->GetRotation().y), D3DXToRadian(m_pTransform->GetRotation().x), D3DXToRadian(m_pTransform->GetRotation().z));
	D3DXVec3TransformCoord(&a, &a, &rotate);

	m_velocity = a;

	if (m_velocity.y != 0)
		m_groundCheck = false;

	m_pTransform->SetPosition(m_pTransform->GetPosition() + (GET_DT * m_velocity));

}



void CRigidBodyComponent::ElasticCollision(std::vector<CGameObject*>& obj)
{
	if (m_velocity.y == 0)
		return;

	bool init = false;

	for (auto& collisionObj : obj)
	{
		if (collisionObj == GetOwner())
			continue;

		SHARED(CRigidBodyComponent) rigdbody = collisionObj->GetComponent<CRigidBodyComponent>();
		if (rigdbody != nullptr)
		{
			_float m1 = m_mass; 
			_float3 v1i = m_velocity;
			_float m2 = rigdbody->GetMass();
			_float3 v2i = rigdbody->GetVelocity();
			_float3 value1 = v1i - v2i;
			_float3 value2 = (-1 * v1i) + v2i;
			_float3 value3 = value1 + value2;

			v1i = value3 / 2;
			v2i = (-1 * v1i) - value1;

			rigdbody->SetVelocity(v2i);
			m_velocity = v1i;
			init = true;
			break;
		}
	}

	if (!init)
	{
		m_velocity = (-1 * m_velocity) * m_bounciness;

		if (m_velocity.y <= 0.4f)
		{
			m_velocity.y = 0;
			m_groundCheck = true;
		}
	}
}

void CRigidBodyComponent::DecelerationFunction(std::vector<CGameObject*>& col)
{
	if (m_separatingVelocity != FLOAT3_ZERO)
	{
		if (m_separatingVelocity.y >= -0.1f && m_separatingVelocity.y < 0)
			m_separatingVelocity.y = 0;

		m_pTransform->SetPosition(m_pTransform->GetPosition() - (m_separatingVelocity));
		m_separatingVelocity = FLOAT3_ZERO;
	}

	if (m_velocity != FLOAT3_ZERO)
	{
		if(m_velocity.z > 0)
			m_velocity.z = MathfMax(m_velocity.z - (GET_DT * m_damping), 0);
		else if (m_velocity.z < 0)
			m_velocity.z = MathfMin(m_velocity.z + (GET_DT * m_damping), 0);

		if (m_velocity.x > 0)
			m_velocity.x = MathfMax(m_velocity.x - (GET_DT * m_damping), 0);
		else if (m_velocity.x < 0)
			m_velocity.x = MathfMin(m_velocity.x + (GET_DT * m_damping), 0);
	}
}
