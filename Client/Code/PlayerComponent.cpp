#include "stdafx.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DataStore.h"
#include "WndApp.h"
#include "SoundManager.h"


CPlayerComponent::CPlayerComponent()
{
}


CPlayerComponent::~CPlayerComponent()
{
}

SHARED(Engine::CComponent) CPlayerComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CPlayerComponent) pClone(new CPlayerComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CPlayerComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
	m_pOwner->SetLayerKey(L"Player");
	m_pOwner->SetObjectKey(L"Player");
}

void CPlayerComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);

	Engine::GET_VALUE(true, m_pOwner->GetLayerKey(), m_pOwner->GetObjectKey(), L"m_jumpForce", m_jumpForce);
	Engine::GET_VALUE(true, m_pOwner->GetLayerKey(), m_pOwner->GetObjectKey(), L"m_moveSpeed", m_moveSpeed);


	m_pTransform = m_pOwner->GetComponent<Engine::CTransformComponent>();
	m_pGraphics = m_pOwner->GetComponent<Engine::CGraphicsComponent>();

	if (Engine::GET_CUR_SCENE->GetName() == L"EventScene")
	{
		m_pOwner->GetComponent<Engine::CRigidBodyComponent>()->SetMass(0.f);
		m_pOwner->GetComponent<Engine::CRigidBodyComponent>()->SetBounciness(0.f);
	}

	m_spCamTransform = Engine::GET_CUR_SCENE->GetMainCamera()->GetOwner()->GetComponent<Engine::CTransformComponent>();

	if (auto& pCC = m_pOwner->GetComponent<Engine::CColliderComponent>())
		pCC->SetColliderID((_int)EColliderID::Player);
}

_uint CPlayerComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CPlayerComponent::Update(SHARED(Engine::CComponent) spThis)
{
	Move();
	if (!Engine::GET_CUR_SCENE->GetMainCamera()->GetCameraEvent() && Engine::GET_CUR_SCENE->GetName() != L"EventScene")
	{
		
		PlayerMousePicking();
		if (Engine::GET_CUR_SCENE->GetMainCamera()->GetIsStarted())
			Engine::GET_CUR_SCENE->GetMainCamera()->CameraRotation();

		//m_spCamTransform->SetPosition(m_pTransform->GetPosition());
		//m_pTransform->SetRotationY(m_spCamTransform->GetRotation().y);
	}

	return _uint();
}

_uint CPlayerComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CPlayerComponent::OnDestroy(void)
{
}

void CPlayerComponent::OnEnable(void)
{
	__super::OnEnable();
}

void CPlayerComponent::OnDisable(void)
{
	__super::OnDisable();
}


void CPlayerComponent::Move(void)
{

	if (Engine::IMKEY_DOWN(KEY_SPACE) && m_pOwner->GetComponent<Engine::CRigidBodyComponent>()->GetGroundCheck())
	{
		m_pOwner->GetComponent<Engine::CRigidBodyComponent>()->AddForce(FLOAT3_UP * m_jumpForce);
	}

	if (Engine::IMKEY_PRESS(KEY_W))
	{
		m_pOwner->GetComponent<Engine::CTransformComponent>()->Translate(_float3(0, 1, 0) *  m_moveSpeed);
		//Engine::CSoundManager::GetInstance()->StartSound(L"PlayerWark.wav", Engine::CHANNELID::PLAYER);
	}

	if (Engine::IMKEY_PRESS(KEY_S))
	{

		m_pOwner->GetComponent<Engine::CTransformComponent>()->Translate(_float3(0, -1, 0) *  m_moveSpeed);
		//Engine::CSoundManager::GetInstance()->StartSound(L"PlayerWark.wav", Engine::CHANNELID::PLAYER);

	}

	if (Engine::IMKEY_PRESS(KEY_A))
	{

		m_pOwner->GetComponent<Engine::CTransformComponent>()->Translate(_float3(-1, 0, 0) *  m_moveSpeed);
		//Engine::CSoundManager::GetInstance()->StartSound(L"PlayerWark.wav", Engine::CHANNELID::PLAYER);

	}

	if (Engine::IMKEY_PRESS(KEY_D))
	{
		//if (!CheckBlocksForRayCollision(FLOAT3_RIGHT))
		//{
		m_pOwner->GetComponent<Engine::CTransformComponent>()->Translate(_float3(1, 0, 0) *  m_moveSpeed);
		//Engine::CSoundManager::GetInstance()->StartSound(L"PlayerWark.wav", Engine::CHANNELID::PLAYER);
	//}
	}

	
}

void CPlayerComponent::PlayerMousePicking()
{
	_float3 temp = {};
	Engine::CGameObject* block = Engine::CInputManager::GetInstance()->MousePicking(L"EventBlock", temp);


	// 좌클릭 했을 때 각 색깔마다의 기능 구현
	if (Engine::CInputManager::GetInstance()->KeyDown(MOUSE_LEFT) && block)
	{
		if (block->GetObjectKey() == L"RedBlock")
		{
			auto& blockCom = block->GetComponent<CRedBlockComponent>();

			if (blockCom->GetActivatedLv() == blockCom->GetMaxActivatedLv())
				return;

			blockCom->SetLButton(true);
			blockCom->SetRButton(false);

			block->GetComponent<CRedBlockComponent>()->SetCheckInteractBlockWithLBtn(true);
		}
		else if (block->GetObjectKey() == L"BlueBlock")
		{
			auto& blockCom = block->GetComponent<CBlueBlockComponent>();

			if (blockCom->GetActivatedLv() == blockCom->GetMaxActivatedLv())
				return;

			blockCom->SetLButton(true);
			blockCom->SetRButton(false);

			block->GetComponent<CBlueBlockComponent>()->SetCheckInteractBlockWithLBtn(true);
		}
		else if (block->GetObjectKey() == L"YellowBlock")
		{
			auto& blockCom = block->GetComponent<CYellowBlockComponent>();

			if (blockCom->GetActivatedLv() == blockCom->GetMaxActivatedLv())
				return;

			blockCom->SetLButton(true);
			blockCom->SetRButton(false);

			block->GetComponent<CYellowBlockComponent>()->SetCheckInteractBlockWithLBtn(true);
		}
	}

	// 우클릭 했을 때 각 색깔마다의 기능 구현
	if (Engine::CInputManager::GetInstance()->KeyDown(MOUSE_RIGHT) && block)
	{
		if (block->GetObjectKey() == L"RedBlock")
		{
			auto& blockCom = block->GetComponent<CRedBlockComponent>();

			if (0 == blockCom->GetActivatedLv())
				return;

			blockCom->SetLButton(false);
			blockCom->SetRButton(true);

			block->GetComponent<CRedBlockComponent>()->SetCheckInteractBlockWithRBtn(true);
		}
		else if (block->GetObjectKey() == L"BlueBlock")
		{
			auto& blockCom = block->GetComponent<CBlueBlockComponent>();

			//if (0 == blockCom->GetActivatedLv())
			//   return;

			blockCom->SetLButton(false);
			blockCom->SetRButton(true);

			block->GetComponent<CBlueBlockComponent>()->SetCheckInteractBlockWithRBtn(true);
		}
		else if (block->GetObjectKey() == L"YellowBlock")
		{
			auto& blockCom = block->GetComponent<CYellowBlockComponent>();

			if (0 == blockCom->GetActivatedLv())
				return;

			blockCom->SetLButton(false);
			blockCom->SetRButton(true);

			block->GetComponent<CYellowBlockComponent>()->SetCheckInteractBlockWithRBtn(true);
		}
	}
}

_float3 CPlayerComponent::GetPlayerDir(_float3 dir)
{
	_float3 playerDir = dir;
	_float3 playerRotation = m_pOwner->GetComponent<Engine::CTransformComponent>()->GetRotation();
	_mat rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(playerRotation.y), D3DXToRadian(playerRotation.x), D3DXToRadian(playerRotation.z));
	D3DXVec3TransformCoord(&playerDir, &playerDir, &rotate);

	return playerDir;
}

_bool CPlayerComponent::CheckBlocksForRayCollision(_float3 direction)
{
	_float3 rayPos = m_pOwner->GetComponent<Engine::CTransformComponent>()->GetPosition();
	_float3 playerDir = GetPlayerDir(direction);

	if (direction != FLOAT3_UP &&	direction != FLOAT3_DOWN)
	{
		rayPos.y -= m_pOwner->GetComponent<Engine::CTransformComponent>()->GetScale().y / 3;
	}

	if (Engine::CInputManager::GetInstance()->RayCast(rayPos, playerDir, PLAYER_RAY_DISTANCE, L"NormalBlock"))
	{
		return true;
	}
	else if (Engine::CInputManager::GetInstance()->RayCast(rayPos, playerDir, PLAYER_RAY_DISTANCE, L"EventBlock"))
	{
		return true;
	}

	return false;
}