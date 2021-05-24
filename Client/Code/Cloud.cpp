#include "stdafx.h"
#include "Cloud.h"
#include "Player.h"

_uint CCloud::m_s_uniqueID = 0;

CCloud::CCloud()
{
}


CCloud::~CCloud()
{
	OnDestroy();
}

SP(CCloud) CCloud::Create(_bool isStatic)
{
	SP(CCloud) spInstance(new CCloud, Engine::SmartDeleter<CCloud>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CCloud::MakeClone(void)
{
	SP(CCloud) spClone(new CCloud, Engine::SmartDeleter<CCloud>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	return spClone;
}

void CCloud::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Map;
	m_dataID	= (_int)EDataID::Scene;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
}

void CCloud::Start(void)
{
	__super::Start();

	m_spTransform->SetSize(0.005f, 0.005f, 0.005f);
	m_originPos = m_spTransform->GetPosition();
	AddComponent<Engine::CDebugC>();
}

void CCloud::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CCloud::Update(void)
{
	__super::Update();
	if (m_spTransform->GetPosition() != m_originPos && m_spTransform->GetLerpOn() == false)
	{
		m_spTransform->SetGoalPosition(m_originPos);
		m_spTransform->SetLerpSpeed(10);
		m_spTransform->SetLerpOn(true);
	}
}

void CCloud::LateUpdate(void)
{
	__super::LateUpdate();
}

void CCloud::OnDestroy(void)
{
	__super::OnDestroy();
}

void CCloud::OnEnable(void)
{
	__super::OnEnable();
	
}

void CCloud::OnDisable(void)
{
	__super::OnDisable();
}

void CCloud::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CCloud::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.normal.y > 0.5f)
	{
		SP(Engine::CRigidBodyC) spOtherRigid = ci.pOtherCollider->GetOwner()->GetRigidbody();
		if (spOtherRigid != nullptr)
			spOtherRigid->AddForce(_float3(0, 300, 0));

		m_spTransform->SetGoalPosition(m_spTransform->GetPosition() - _float3(0, 0.3f, 0));
		m_spTransform->SetLerpSpeed(5);
		m_spTransform->SetLerpOn(true);

		static_cast<CPlayer*>(ci.pOtherCollider->GetOwner()->m_pObject)->SetIsHurt(true);
	}
}

void CCloud::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CCloud::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
