#include "stdafx.h"
#include "PlayerAttack.h"
#include "Mafia.h"

_uint CPlayerAttack::m_s_uniqueID = 0;

CPlayerAttack::CPlayerAttack()
{
}


CPlayerAttack::~CPlayerAttack()
{
	OnDestroy();
}

SP(CPlayerAttack) CPlayerAttack::Create(_bool isStatic)
{
	SP(CPlayerAttack) spInstance(new CPlayerAttack, Engine::SmartDeleter<CPlayerAttack>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPlayerAttack::MakeClone(void)
{
	SP(CPlayerAttack) spClone(new CPlayerAttack, Engine::SmartDeleter<CPlayerAttack>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CPlayerAttack::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Player;
	m_dataID = (_int)EDataID::Player;

	m_spCollision = AddComponent<Engine::CCollisionC>();
}

void CPlayerAttack::Start(void)
{
	__super::Start();
	AddComponent<Engine::CDebugC>();
}

void CPlayerAttack::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CPlayerAttack::Update(void)
{
	__super::Update();
	
}

void CPlayerAttack::LateUpdate(void)
{
	__super::LateUpdate();
	
	if (m_lastFrameEnabled)
	{
		m_lastFrameEnabled = false;
		m_isEnabled = false;
	}
	else
		m_lastFrameEnabled = true;
}

void CPlayerAttack::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CPlayerAttack::OnEnable(void)
{
	__super::OnEnable();
	
}

void CPlayerAttack::OnDisable(void)
{
	__super::OnDisable();
	
}

void CPlayerAttack::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CPlayerAttack::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.pOtherCollider->GetOwner()->GetOwner()->GetObjectKey() == L"Mafia")
	{
		CMafia* pMafia = 
			static_cast<CMafia*>(ci.pOtherCollider->GetOwner()->m_pObject);

		pMafia->SetIsHurt(true);
	}
}

void CPlayerAttack::OnCollisionStay(Engine::_CollisionInfo ci)
{
	if (ci.pOtherCollider->GetOwner()->GetOwner()->GetObjectKey() == L"Mafia")
	{
		CMafia* pMafia =
			static_cast<CMafia*>(ci.pOtherCollider->GetOwner()->m_pObject);

		pMafia->SetIsHurt(true);
	}
}

void CPlayerAttack::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
