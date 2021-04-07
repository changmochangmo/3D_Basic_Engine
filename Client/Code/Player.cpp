#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "FRC.h"

_uint CPlayer::m_s_uniqueID = 0;

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

SP(CPlayer) CPlayer::Create(void)
{
	SP(CPlayer) spPlayer(new CPlayer, Engine::SmartDeleter<CPlayer>);
	spPlayer->Awake();

	return spPlayer;
}

SP(Engine::CGameObject) CPlayer::MakeClone(void)
{
	SP(CPlayer) spClone(new CPlayer, Engine::SmartDeleter<CPlayer>);
	__super::InitClone(spClone);

	return spClone;
}

//현재 프로토타입만 어웨이크를 타고, 클론은 어웨이크가 된 프로토타입을 복사해감.
void CPlayer::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Player;
	m_dataID	= (_int)EDataID::Player;

	m_spTransform	= AddComponent<Engine::CTransformC>();
	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
}

void CPlayer::Start(void)
{
	__super::Start();
	m_spTransform	= GetComponent<Engine::CTransformC>();
	m_spMesh		= GetComponent<Engine::CMeshC>();
	m_spTexture		= GetComponent<Engine::CTextureC>();
	m_spGraphics	= GetComponent<Engine::CGraphicsC>();

	m_spTransform->SetScale(_float3(1.f, 1.f, 2.f));

	//m_spTransform->SetRotation(_float3(45, 45, 0));
	//m_spTransform->UpdateLookAt();
	//m_spTransform->UpdateWorldMatrix();
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
		//_float3 vec(-1, -1, -1);
		//D3DXVec3Normalize(&vec, &vec);
		//m_spTransform->SetLookAt(vec);
		//m_spTransform->UpdateRotation();
		m_spTransform->SetForward(m_spTransform->GetForward() + _float3(1, 0, 0) * GET_DT);
	}
	if (Engine::IMKEY_PRESS(KEY_LEFT))
	{
		m_spTransform->SetForward(m_spTransform->GetForward() + _float3(-1, 0, 0) * GET_DT);
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

void CPlayer::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
