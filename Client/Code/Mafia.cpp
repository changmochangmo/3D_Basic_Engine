#include "stdafx.h"
#include "Mafia.h"


_uint CMafia::m_s_uniqueID = 0;

CMafia::CMafia()
{
}


CMafia::~CMafia()
{
	OnDestroy();
}

SP(CMafia) CMafia::Create(_bool isStatic)
{
	SP(CMafia) spInstance(new CMafia, Engine::SmartDeleter<CMafia>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMafia::MakeClone(void)
{
	SP(CMafia) spClone(new CMafia, Engine::SmartDeleter<CMafia>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();

	return spClone;
}

void CMafia::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Enemy;
	m_dataID	= (_int)EDataID::Enemy;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();

	m_spTransform->SetSize(_float3(0.01f, 0.01f, 0.01f));
	m_spTransform->SetRotationY(PI);
}

void CMafia::Start(void)
{
	__super::Start();
}

void CMafia::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMafia::Update(void)
{
	__super::Update();
	
}

void CMafia::LateUpdate(void)
{
	if (m_onGround)
	{
		m_spRigidBody->AddForce(-GRAVITY * m_spRigidBody->GetGravityConstant());
	}

	__super::LateUpdate();
	
}

void CMafia::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CMafia::OnEnable(void)
{
	__super::OnEnable();
	
}

void CMafia::OnDisable(void)
{
	__super::OnDisable();
	
}

void CMafia::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMafia::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.pOtherCollider->GetOwner()->GetCollisionID() == (_int)EColliderID::Map)
	{
		if (ci.normal.y < -0.7)
		{
			m_onGround = true;
			m_spRigidBody->SetVelocityY(0);
		}
	}
}

void CMafia::OnCollisionStay(Engine::_CollisionInfo ci)
{
	if (ci.normal.y < -0.7)
	{
		m_onGround = true;
	}
}

void CMafia::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
