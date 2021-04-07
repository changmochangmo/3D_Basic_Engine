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
}

SP(CComponent) CRigidBodyC::MakeClone(CGameObject * pObject)
{
	SP(CRigidBodyC) spClone(new CRigidBodyC);
	__super::InitClone(spClone, pObject);

	spClone->SetMass(m_mass);
	spClone->SetDrag(m_drag);
	spClone->SetUseGravity(m_useGravity);
	spClone->SetFreezePosition(m_freezePosition);
	spClone->SetFreezeRotation(m_freezeRotation);
	spClone->SetGroundCheck(m_groundCheck);
	spClone->SetVelocity(m_velocity);
	spClone->SetBounciness(m_bounciness);


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
	m_pTransform = m_pOwner->GetComponent<CTransformC>().get();
	m_mass = GET_MATH->Min(m_mass, 100);
	m_mass /= 100;
	m_bounciness = GET_MATH->Min(m_bounciness, 1);
	m_separatingVelocity = ZERO_VECTOR;
}

void CRigidBodyC::FixedUpdate(SP(CComponent) spThis)
{
	std::vector<CGameObject*> col;
	SP(CCollisionC) spCC = m_pOwner->GetComponent<CCollisionC>();

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

	m_netForce = ZERO_VECTOR;
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

void CRigidBodyC::GravityDrag(_float3 & velocity)
{
	_float3 drag = velocity;
	D3DXVec3Normalize(&drag, &drag);

	velocity.y += GRAVITY.y * GET_DT;

	/*drag.y = -drag.y * ((1 - drag.y) + (10 * (drag.y * drag.y)));
	velocity.y -= drag.y;*/
}

void CRigidBodyC::AddForce(_float3 force)
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

void CRigidBodyC::SetForce(_float3 force)
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

void CRigidBodyC::TranslateForce(_float3 force)
{
	_float xForce = (force.x / m_mass);
	_float yForce = (force.y / m_mass);
	_float zForce = (force.z / m_mass);

	_float3 a = _float3(xForce, yForce, zForce);

	_mat rotate;

	//ÄõÅÍ´Ï¾È
	//D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_pTransform->GetRotation().y), D3DXToRadian(m_pTransform->GetRotation().x), D3DXToRadian(m_pTransform->GetRotation().z));
	D3DXVec3TransformCoord(&a, &a, &rotate);

	m_velocity = a;

	if (m_velocity.y != 0)
		m_groundCheck = false;

	m_pTransform->SetPosition(m_pTransform->GetPosition() + (GET_DT * m_velocity));

}



void CRigidBodyC::ElasticCollision(std::vector<CGameObject*>& obj)
{
	if (m_velocity.y == 0)
		return;

	bool init = false;

	for (auto& collisionObj : obj)
	{
		if (collisionObj == GetOwner())
			continue;

		SP(CRigidBodyC) rigdbody = collisionObj->GetComponent<CRigidBodyC>();
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

void CRigidBodyC::DecelerationFunction(std::vector<CGameObject*>& col)
{
	if (m_separatingVelocity != ZERO_VECTOR)
	{
		if (m_separatingVelocity.y >= -0.1f && m_separatingVelocity.y < 0)
			m_separatingVelocity.y = 0;

		m_pTransform->SetPosition(m_pTransform->GetPosition() - (m_separatingVelocity));
		m_separatingVelocity = ZERO_VECTOR;
	}

	if (m_velocity != ZERO_VECTOR)
	{
		if(m_velocity.z > 0)
			m_velocity.z = GET_MATH->Max(m_velocity.z - (GET_DT * m_damping), 0);
		else if (m_velocity.z < 0)
			m_velocity.z = GET_MATH->Min(m_velocity.z + (GET_DT * m_damping), 0);

		if (m_velocity.x > 0)
			m_velocity.x = GET_MATH->Max(m_velocity.x - (GET_DT * m_damping), 0);
		else if (m_velocity.x < 0)
			m_velocity.x = GET_MATH->Min(m_velocity.x + (GET_DT * m_damping), 0);
	}
}
