#include "stdafx.h"
#include "SandBag.h"
#include "FRC.h"

_uint CSandBag::m_s_uniqueID = 0;

CSandBag::CSandBag()
{
}


CSandBag::~CSandBag()
{
	OnDestroy();
}

SP(CSandBag) CSandBag::Create(_bool isStatic)
{
	SP(CSandBag) spInstance(new CSandBag, Engine::SmartDeleter<CSandBag>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSandBag::MakeClone(void)
{
	SP(CSandBag) spClone(new CSandBag, Engine::SmartDeleter<CSandBag>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();
	return spClone;
}

void CSandBag::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Enemy;
	m_dataID	= (_int)EDataID::Enemy;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();

	m_spTransform->SetSize(0.01f, 0.01f, 0.01f);
	m_isEnabled = false;
}

void CSandBag::Start(void)
{
	__super::Start();

	m_startPos = _float3(-14.5f, 6.f, 65.75f);
	m_interval = 1.5f;
	m_readyPosY = 5.5f;

	m_spTransform->SetPosition(m_startPos);
	m_spTransform->AddPositionX(m_interval * m_laneNumber);
	m_spRigidBody->SetUseGravity(false);

	AddComponent<Engine::CDebugC>();
}

void CSandBag::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSandBag::Update(void)
{
	__super::Update();

	_float deltaTime = GET_DT;

	if (m_ready == false)
	{
		m_spTransform->AddPositionY(-1 * deltaTime);
		if (m_spTransform->GetPosition().y <= m_readyPosY)
			m_ready = true;
	}
	else
	{
		m_fallingTimer += deltaTime;
		if (m_fallingTimer >= m_fallingDuration)
			m_spRigidBody->SetUseGravity(true);
	}
	
}

void CSandBag::LateUpdate(void)
{
	__super::LateUpdate();
}

void CSandBag::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CSandBag::OnEnable(void)
{
	__super::OnEnable();
	
}

void CSandBag::OnDisable(void)
{
	__super::OnDisable();
	
}

void CSandBag::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CSandBag::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	m_spRigidBody->SetVelocity(ZERO_VECTOR);
	m_spRigidBody->SetUseGravity(false);
	m_spTransform->SetPosition(m_startPos);
	m_spTransform->AddPositionX(m_interval * m_laneNumber);

	m_ready = false;
	m_fallingTimer = 0.f;
	m_isEnabled = false;
}

void CSandBag::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CSandBag::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
