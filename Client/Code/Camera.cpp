#include "stdafx.h"
#include "Camera.h"

#include "DebugCollider.h"
_uint CCamera::m_s_uniqueID = 0;

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

SP(CCamera) CCamera::Create(void)
{
	SP(CCamera) spInstance(new CCamera, Engine::SmartDeleter<CCamera>);
	spInstance->SetIsStatic(true);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CCamera::MakeClone(void)
{
	SP(CCamera) spClone(new CCamera, Engine::SmartDeleter<CCamera>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spCamera		= spClone->GetComponent<Engine::CCameraC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug		= spClone->GetComponent<Engine::CDebugC>();

	return spClone;
}

void CCamera::Awake(void)
{
	__super::Awake();
	m_layerID	= (_int)ELayerID::Camera;
	m_dataID	= (_int)EDataID::Camera;

	m_spCamera		= AddComponent<Engine::CCameraC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spDebug		= AddComponent<Engine::CDebugC>();
	
	m_spTransform->SetPosition(100, 100, 100);
	m_spCollision->SetResolveIn(false);
}

void CCamera::Start(void)
{
	__super::Start();
	m_pCamRayCollider = static_cast<Engine::CRayCollider*>(m_spCollision->GetColliders()[0]);
	m_pCamRayCollider->SetTarget(m_spCamera->GetTarget().get());
}

void CCamera::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CCamera::Update(void)
{
	__super::Update();
	
	m_spCamera->SetTargetDist(3.f);
	
}

void CCamera::LateUpdate(void)
{
	__super::LateUpdate();

	_float3 playerPos = m_spCamera->GetTarget()->GetTransform()->GetPosition() + m_spCamera->GetTargetOffset();
	_float3 myPos = m_spTransform->GetPosition();
	_float3 dir = playerPos - myPos;
	D3DXVec3Normalize(&dir, &dir);
	if (m_spCamera->GetMode() == Engine::ECameraMode::Follower)
		m_pCamRayCollider->SetLength(m_spCamera->GetTargetDist());
	else
		m_pCamRayCollider->SetLength(1.f);
}

void CCamera::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CCamera::OnEnable(void)
{
	__super::OnEnable();
	
}

void CCamera::OnDisable(void)
{
	__super::OnDisable();
	
}

void CCamera::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CCamera::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	_float length = D3DXVec3Length(&(m_spCamera->GetTarget()->GetTransform()->GetPosition() - m_spTransform->GetPosition()));
	m_pCamRayCollider->SetLength(length);
	m_spCamera->SetTargetDist(length);
}

void CCamera::OnCollisionStay(Engine::_CollisionInfo ci)
{
	_float length = D3DXVec3Length(&(m_spCamera->GetTarget()->GetTransform()->GetPosition() - m_spTransform->GetPosition()));
	m_pCamRayCollider->SetLength(length);
	m_spCamera->SetTargetDist(length);
}

void CCamera::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
