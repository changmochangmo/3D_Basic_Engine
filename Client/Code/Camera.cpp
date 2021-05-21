#include "stdafx.h"
#include "Camera.h"

#include "FRC.h"
#include "DebugCollider.h"
#include "TextManager.h"
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

	return spClone;
}

void CCamera::Awake(void)
{
	__super::Awake();
	m_layerID	= (_int)ELayerID::Camera;
	m_dataID	= (_int)EDataID::Camera;

	m_spCamera		= AddComponent<Engine::CCameraC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	
	m_spTransform->SetPosition(0, 0, -360);
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
	
	_float curTargetDist = m_spCamera->GetTargetDist();
	if (m_wallCollided == false && curTargetDist < 3)
	{
		_float newTargetDist = m_spCamera->GetTargetDist() + GET_DT;

		newTargetDist = GET_MATH->Min(newTargetDist, 3);
		m_spCamera->SetTargetDist(newTargetDist);		
	}
}

void CCamera::LateUpdate(void)
{
	__super::LateUpdate();

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
	m_spTransform->AddPosition(ci.normal * ci.penetLength);
	m_wallCollided = true;
	if (m_spCamera->GetTarget() != nullptr)
	{
		_float3 targetPos = m_spCamera->GetTarget()->GetTransform()->GetPosition() + _float3(0, 0.5f, 0);
		_float3 targetDir = targetPos - m_spTransform->GetPosition();
		D3DXVec3Normalize(&targetDir, &targetDir);

		_float targetDist = D3DXVec3Length(&(targetPos - m_spTransform->GetPosition()));

		m_pCamRayCollider->SetLength(targetDist);
		m_pCamRayCollider->SetDirection(targetDir);
		m_spCamera->SetTargetDist(targetDist);
	}
}

void CCamera::OnCollisionStay(Engine::_CollisionInfo ci)
{
	m_spTransform->AddPosition(ci.normal * ci.penetLength);
	if (m_spCamera->GetTarget() != nullptr)
	{
		_float3 targetPos = m_spCamera->GetTarget()->GetTransform()->GetPosition() + _float3(0, 0.5f, 0);
		_float3 targetDir = targetPos - m_spTransform->GetPosition();
		D3DXVec3Normalize(&targetDir, &targetDir);

		_float targetDist = D3DXVec3Length(&(targetPos - m_spTransform->GetPosition()));

		m_pCamRayCollider->SetLength(targetDist);
		m_pCamRayCollider->SetDirection(targetDir);
		m_spCamera->SetTargetDist(targetDist);
	}
}

void CCamera::OnCollisionExit(Engine::_CollisionInfo ci)
{
	m_wallCollided = false;
}
