#include "stdafx.h"
#include "MafiaBall.h"
#include "FRC.h"

_uint CMafiaBall::m_s_uniqueID = 0;
CMafiaBall::CMafiaBall()
{
}


CMafiaBall::~CMafiaBall()
{
	OnDestroy();
}

SP(CMafiaBall) CMafiaBall::Create(_bool isStatic)
{
	SP(CMafiaBall) spInstance(new CMafiaBall, Engine::SmartDeleter<CMafiaBall>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMafiaBall::MakeClone(void)
{
	SP(CMafiaBall) spClone(new CMafiaBall, Engine::SmartDeleter<CMafiaBall>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	return spClone;
}

void CMafiaBall::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Enemy;
	m_dataID	= (_int)EDataID::Enemy;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();

	m_spTransform->SetSize(0.01f, 0.01f, 0.01f);
	m_isEnabled = true;
}

void CMafiaBall::Start(void)
{
	__super::Start();

	m_spTransform->SetPositionX(-3.7f);
	m_spTransform->SetPositionY(0.8);
	m_spTransform->SetPositionZ(64.75f);
	
	AddComponent<Engine::CDebugC>();
	//_float yPos = 1.3f + m_spTransform->GetSize().y * 95;
	//m_spTransform->SetPositionY(yPos);
	//static_cast<Engine::CSphereCollider*>(m_spCollision->GetColliders()[0])->SetRadius(m_spTransform->GetSize().y * 190);
	//static_cast<Engine::CSphereCollider*>(m_spCollision->GetColliders()[1])->SetRadius(m_spTransform->GetSize().y * 95);
	//static_cast<Engine::CSphereCollider*>(m_spCollision->GetColliders()[1])->SetOffsetOrigin(_float3(0, -m_spTransform->GetSize().y * 95, 1));
}

void CMafiaBall::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CMafiaBall::Update(void)
{
	__super::Update();
	
	

	m_spTransform->AddRotationZ(PI / 4 * GET_DT);
}

void CMafiaBall::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CMafiaBall::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CMafiaBall::OnEnable(void)
{
	__super::OnEnable();
	
}

void CMafiaBall::OnDisable(void)
{
	__super::OnDisable();
	
}

void CMafiaBall::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMafiaBall::OnCollisionEnter(Engine::_CollisionInfo ci)
{
}

void CMafiaBall::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CMafiaBall::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
