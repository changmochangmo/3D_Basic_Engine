#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "FRC.h"
#include "DynamicMesh.h"
#include "MeshData.h"
#include "CameraManager.h"

_uint CPlayer::m_s_uniqueID = 0;

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

SP(CPlayer) CPlayer::Create(_bool isStatic)
{
	SP(CPlayer) spInstance(new CPlayer, Engine::SmartDeleter<CPlayer>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPlayer::MakeClone(void)
{
	SP(CPlayer) spClone(new CPlayer, Engine::SmartDeleter<CPlayer>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	return spClone;
}

//현재 프로토타입만 어웨이크를 타고, 클론은 어웨이크가 된 프로토타입을 복사해감.
void CPlayer::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Player;
	m_dataID	= (_int)EDataID::Player;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();

	m_spTransform->SetSize(_float3(0.01f, 0.01f, 0.01f));
}

void CPlayer::Start(void)
{
	__super::Start();
}

void CPlayer::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CPlayer::Update(void)
{
	__super::Update();

	m_status = Idle;

	UpdateMovement();
	UpdateAnimation();
	m_lastStatus = m_status;
}

void CPlayer::LateUpdate(void)
{
	__super::LateUpdate();
}

void CPlayer::OnDestroy(void)
{
	__super::OnDestroy();
}

void CPlayer::OnEnable(void)
{
	__super::OnEnable();
}

void CPlayer::OnDisable(void)
{
	__super::OnDisable();
}

void CPlayer::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}


void CPlayer::OnCollisionEnter(Engine::_CollisionInfo ci)
{
}

void CPlayer::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CPlayer::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CPlayer::UpdateAnimation(void)
{
	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();

	if (m_lastStatus != m_status)
	{
		_int aniIndex;
		_float aniSpeed;
		switch (m_status)
		{
		case Idle:
			aniIndex = ANI_IDLE;
			aniSpeed = 1.f;
			break;

		case Walk:
			aniIndex = ANI_RUN;
			aniSpeed = 2.f;
			break;

		case Run:
			aniIndex = ANI_RUN;
			aniSpeed = 3.f;
			break;
		}
		for (_int i = 0; i < (_int)vMeshData.size(); ++i)
		{
			Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[i]);
			pDM->ChangeAniSet(aniIndex);
			pDM->GetAniCtrl()->SetSpeed(aniSpeed);
		}
	}
}

void CPlayer::UpdateMovement(void)
{
	SP(Engine::CTransformC) mainCamTransform = Engine::GET_MAIN_CAM->GetOwner()->GetTransform();

	m_moveDir = ZERO_VECTOR;

	if (Engine::IMKEY_PRESS(KEY_W))
	{
		_float3 dir = m_spTransform->GetPosition() - mainCamTransform->GetPosition();
		dir.y = 0; 
		D3DXVec3Normalize(&dir, &dir);
		m_moveDir += dir;
	}
	if (Engine::IMKEY_PRESS(KEY_A))
	{
		_float3 dir = m_spTransform->GetPosition() - mainCamTransform->GetPosition();
		dir.y = 0;
		D3DXVec3Normalize(&dir, &dir);
		D3DXVec3Cross(&dir, &dir, &UP_VECTOR);

		m_moveDir += dir;
	}
	if (Engine::IMKEY_PRESS(KEY_S))
	{
		_float3 dir = mainCamTransform->GetPosition() - m_spTransform->GetPosition();
		dir.y = 0;
		D3DXVec3Normalize(&dir, &dir);

		m_moveDir += dir;
	}
	if (Engine::IMKEY_PRESS(KEY_D))
	{
		_float3 dir = m_spTransform->GetPosition() - mainCamTransform->GetPosition();
		dir.y = 0;
		D3DXVec3Normalize(&dir, &dir);
		D3DXVec3Cross(&dir, &UP_VECTOR, &dir);

		m_moveDir += dir;
	}
	
	
	D3DXVec3Normalize(&m_moveDir, &m_moveDir);

	if (D3DXVec3LengthSq(&m_moveDir) > EPSILON)
	{
		m_spTransform->SetGoalForward(m_moveDir);

		_float moveSpeed;
		m_status = Walk;
		moveSpeed = m_walkSpeed;
		if (Engine::IMKEY_PRESS(KEY_SHIFT))
		{
			m_status = Run;
			moveSpeed = m_runSpeed;
		}

		m_spTransform->AddPosition(m_moveDir * moveSpeed * GET_DT);
	}
}

