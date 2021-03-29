#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

SHARED(CPlayer) CPlayer::Create(void)
{
	SHARED(CPlayer) spPlayer(new CPlayer, Engine::SmartDeleter<CPlayer>);
	spPlayer->Awake();

	return spPlayer;
}

SHARED(Engine::CGameObject) CPlayer::MakeClone(void)
{
	SHARED(CPlayer) spClone(new CPlayer, Engine::SmartDeleter<CPlayer>);
	Engine::CGameObject::InitClone(spClone);

	return spClone;
}

//현재 프로토타입만 어웨이크를 타고, 클론은 어웨이크가 된 프로토타입을 복사해감.
void CPlayer::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Player;
	m_dataID	= (_int)EDataID::Player;

	m_spTransform	= AddComponent<Engine::CTransformComponent>();
	m_spMesh		= AddComponent<Engine::CMeshComponent>();
	m_spTexture		= AddComponent<Engine::CTextureComponent>();
	m_spGraphics	= AddComponent<Engine::CGraphicsComponent>();
}

void CPlayer::Start(void)
{
	__super::Start();
}

_uint CPlayer::FixedUpdate(void)
{
	__super::FixedUpdate();
	return _uint();
}

_uint CPlayer::Update(void)
{
	__super::Update();
	return _uint();
}

_uint CPlayer::LateUpdate(void)
{
	__super::LateUpdate();
	return _uint();
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
