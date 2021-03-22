#include "stdafx.h"
#include "Player.h"
#include "GameObject.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

SHARED(Engine::CComponent) CPlayer::MakeClone(Engine::CGameObject * pObject)
{
	return SHARED(Engine::CComponent)();
}

void CPlayer::Awake(void)
{
	m_pOwner->SetLayerKey(L"PlayerLayer");
	m_pOwner->SetObjectKey(L"Player");
}

void CPlayer::Start(SHARED(CComponent) spThis)
{
}

_uint CPlayer::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CPlayer::Update(SHARED(Engine::CComponent) spSelf)
{

	
	

	return _uint();
}

_uint CPlayer::LateUpdate(SHARED(Engine::CComponent) spSelf)
{
	return _uint();
}

void CPlayer::OnDestroy(void)
{
}

void CPlayer::OnEnable(void)
{
}

void CPlayer::OnDisable(void)
{
}
