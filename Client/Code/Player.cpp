#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "FRC.h"
#include "DynamicMesh.h"

_uint CPlayer::m_s_uniqueID = 0;

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

SP(CPlayer) CPlayer::Create(_bool isStatic)
{
	SP(CPlayer) spPlayer(new CPlayer, Engine::SmartDeleter<CPlayer>);
	spPlayer->SetIsStatic(isStatic);
	spPlayer->Awake();

	return spPlayer;
}

SP(Engine::CObject) CPlayer::MakeClone(void)
{
	SP(CPlayer) spClone(new CPlayer, Engine::SmartDeleter<CPlayer>);
	__super::InitClone(spClone);

	return spClone;
}

//현재 프로토타입만 어웨이크를 타고, 클론은 어웨이크가 된 프로토타입을 복사해감.
void CPlayer::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Player;
	m_dataID = (_int)EDataID::Player;

	m_spTransform = AddComponent<Engine::CTransformC>();
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spDebug = AddComponent<Engine::CDebugC>();
}

void CPlayer::Start(void)
{
	__super::Start();
	m_spTransform = GetComponent<Engine::CTransformC>();
	m_spMesh = GetComponent<Engine::CMeshC>();
	m_spTexture = GetComponent<Engine::CTextureC>();
	m_spGraphics = GetComponent<Engine::CGraphicsC>();
	m_spDebug = GetComponent<Engine::CDebugC>();

	m_spTransform->SetSize(_float3(0.5f, 0.5f, 0.5f));
}

void CPlayer::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CPlayer::Update(void)
{
	__super::Update();

	if (Engine::IMKEY_PRESS(KEY_RIGHT))
	{
		m_spTransform->MoveRight(3 * GET_DT);

	}
	if (Engine::IMKEY_PRESS(KEY_LEFT))
	{
		m_spTransform->MoveLeft(3 * GET_DT);
	}
	if (Engine::IMKEY_PRESS(KEY_UP))
	{
		m_spTransform->MoveForward(3 * GET_DT);
	}
	if (Engine::IMKEY_PRESS(KEY_DOWN))
	{
		m_spTransform->MoveBackward(3 * GET_DT);
	}

	if (Engine::IMKEY_PRESS(KEY_1))
	{
		dynamic_cast<Engine::CDynamicMesh*>(m_spMesh->GetMeshData())->PlayAnimation();
	}
	if (Engine::IMKEY_DOWN(KEY_2))
	{
		static int i = 0;
		dynamic_cast<Engine::CDynamicMesh*>(m_spMesh->GetMeshData())->ChangeAniSet(i++);
	}

	if (Engine::IMKEY_PRESS(KEY_4))
	{
		Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(m_spMesh->GetMeshData());

		pDM->PlayAnimation();

		if (pDM->IsAnimationEnd())
		{
			pDM->ChangeAniSet(pDM->GetAniCtrl()->GetCurIndex() + 1);
		}
	}
	if (Engine::IMKEY_DOWN(KEY_F2))
	{
		Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(m_spMesh->GetMeshData());
		pDM->ChangeAniSet("Stand_Idle");
	}
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

void CPlayer::OnCollisionEnter(Engine::_CollisionInfo ci)
{
}

void CPlayer::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CPlayer::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CPlayer::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
