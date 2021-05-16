#include "stdafx.h"
#include "Boss.h"
#include "TextManager.h"
#include "InputManager.h"

_uint CBoss::m_s_uniqueID = 0;

CBoss::CBoss()
{
}


CBoss::~CBoss()
{
	OnDestroy();
}

SP(CBoss) CBoss::Create(_bool isStatic)
{
	SP(CBoss) spInstance(new CBoss, Engine::SmartDeleter<CBoss>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBoss::MakeClone(void)
{
	SP(CBoss) spClone(new CBoss, Engine::SmartDeleter<CBoss>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();

	return spClone;
}

void CBoss::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Enemy;
	m_dataID	= (_int)EDataID::Boss;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();

	m_spTransform->SetSize(_float3(0.01f, 0.01f, 0.01f));
	m_spTransform->SetRotationY(PI);
}

void CBoss::Start(void)
{
	__super::Start();
	m_spTransform->SetPosition(-7.7f, 2.25f, 68.f);
	//m_spRigidBody->SetUseGravity(false);
}

void CBoss::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBoss::Update(void)
{
	__super::Update();

	if (Engine::IMKEY_DOWN(KEY_RIGHT))
		Jump(_float3(-7.7f, -1.3f, 65.75f), 2);

	Engine::REWRITE_TEXT(L"Test1", std::to_wstring(m_spTransform->GetPosition().x));
}

void CBoss::LateUpdate(void)
{
	if (m_onGround)
	{
		m_spRigidBody->AddForce(-GRAVITY);
	}

	m_onGround = false;
	__super::LateUpdate();
}

void CBoss::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CBoss::OnEnable(void)
{
	__super::OnEnable();
	
}

void CBoss::OnDisable(void)
{
	__super::OnDisable();
	
}

void CBoss::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CBoss::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.pOtherCollider->GetOwner()->GetCollisionID() == (_int)EColliderID::Map &&
		ci.normal.y < -0.7)
	{
		m_onGround = true;
		m_spRigidBody->SetVelocityY(0);
	}
}

void CBoss::OnCollisionStay(Engine::_CollisionInfo ci)
{
	if (ci.normal.y < -0.7)
	{
		m_onGround = true;
	}
}

void CBoss::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CBoss::Jump(_float3 goalPos, _float time)
{
	_float3 horDirection = goalPos - m_spTransform->GetPosition();
	

	m_spRigidBody->SetVelocity((goalPos - m_spTransform->GetPosition()) / time - 0.5f * GRAVITY * time);
	
}
