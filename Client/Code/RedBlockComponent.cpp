#include "stdafx.h"
#include "RedBlockComponent.h"
#include "GameObject.h"
#include "ColliderManager.h"
#include "DataStore.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Scene.h"
#include "SceneManager.h"

CRedBlockComponent::CRedBlockComponent()
{
}


CRedBlockComponent::~CRedBlockComponent()
{
	int i = 0;
}

SHARED(Engine::CComponent) CRedBlockComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CRedBlockComponent) pClone(new CRedBlockComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CRedBlockComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
	m_pOwner->SetObjectKey(L"RedBlock");


	std::wstring sectionKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();
	
	Engine::GET_VALUE(true, sectionKey, objectKey, L"m_activatedLv", m_activatedLv);
	Engine::GET_VALUE(true, sectionKey, objectKey, L"m_maxActivatedLv", m_maxActivatedLv);
}

void CRedBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	auto& pTransformComponent = m_pOwner->GetComponent<Engine::CTransformComponent>();
	m_initialPosition = pTransformComponent->GetPosition();
	m_activationPosition = m_initialPosition;
	pTransformComponent->SetScale({ 1.f, 3.f, 1.f });
}

_uint CRedBlockComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CRedBlockComponent::Update(SHARED(Engine::CComponent) spThis)
{
	if (m_lButton)
	{
		LClicked();

	}
	else if (m_rButton)
	{
		RClicked();
	}
	return _uint();
}

_uint CRedBlockComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CRedBlockComponent::OnDestroy(void)
{
}

void CRedBlockComponent::OnEnable(void)
{
}

void CRedBlockComponent::OnDisable(void)
{
}

void CRedBlockComponent::LClicked()
{
	std::vector<Engine::CGameObject*> returnCollider;
	auto& pTransformComponent = m_pOwner->GetComponent<Engine::CTransformComponent>();

	bool crushCheck = false;
	SHARED(Engine::CColliderComponent) pCC = m_pOwner->GetComponent<Engine::CColliderComponent>();

	if (pCC->GetIsStarted())
		crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(pCC, returnCollider);

	if (crushCheck)
	{
		for (auto& col : returnCollider)
		{
			if (col->GetName() == L"Player"/* || col->GetObjectKey() == L"GreenBlock"*/)
			{
				_float3& colPos = col->GetComponent<Engine::CTransformComponent>()->GetPosition();
				_float3& blockPos = pTransformComponent->GetPosition();

				// 만약 빨간블럭이 이동이 끝나지 않았다면
				if (pTransformComponent->GetPosition() != m_activationPosition)
				{
					_float3 nextColPos = colPos + GetDirectionOfMovement(FLOAT3_UP, pTransformComponent->GetRotation());
					col->GetComponent<Engine::CTransformComponent>()->Lerp(colPos, nextColPos, 1);
				}
			}
			//else if (col->GetObjectKey() == L"GreenBlock") // 초록블럭과 충돌했다면
			//{
			//	_float3& colPos = col->GetComponent<Engine::CTransformComponent>()->GetPosition();
			//	_float3& blockPos = pTransformComponent->GetPosition();

			//	// 만약 빨간블럭이 이동이 끝나지 않았다면
			//	if (pTransformComponent->GetPosition() != m_activationPosition)
			//	{
			//		//// 새로운 초록블럭 y = 블럭의 y + (초록블럭의 높이 / 2) + (블럭의 높이 / 2)
			//		//colPos.y = blockPos.y + (pColTransformComponent->GetScale().y * 0.5f) + (pTransformComponent->GetScale().y * 0.5f);

			//		//_float3 nextColPos = colPos + GetDirectionOfMovement(FLOAT3_UP, pTransformComponent->GetRotation());
			//		_float3 nextColPos = colPos + FLOAT3_LEFT;
			//		col->GetComponent<Engine::CTransformComponent>()->Lerp(colPos, nextColPos, 1);
			//	}
			//}
		}
	}

	if(Engine::GET_CUR_SCENE->GetName() != L"EventScene")
		pTransformComponent->Lerp(pTransformComponent->GetPosition(), m_activationPosition, 1);

	if (m_maxActivatedLv == m_activatedLv)
		return;

	if (m_isInteractBlockWithLBtn)
	{
		if (CheckBlocksForRayCollision(GetDirectionOfMovement(FLOAT3_UP, pTransformComponent->GetRotation())))
		{
			m_isInteractBlockWithLBtn = false;
			return;
		}

		Engine::CSoundManager::GetInstance()->StartSound(L"BoxPush.wav", Engine::CHANNELID::BOX);

		++m_activatedLv;
		m_activationPosition += GetDirectionOfMovement(FLOAT3_UP, pTransformComponent->GetRotation());
		m_isInteractBlockWithLBtn = false;
	}
}

void CRedBlockComponent::RClicked()
{
	std::vector<Engine::CGameObject*> returnCollider;
	bool crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(m_pOwner->GetComponent<Engine::CColliderComponent>(), returnCollider);
	auto& pTransformComponent = m_pOwner->GetComponent<Engine::CTransformComponent>();
	if (crushCheck)
	{
		for (auto& col : returnCollider)
		{
			auto& pColTransformComponent = col->GetComponent<Engine::CTransformComponent>();
			_float3& colPos = pColTransformComponent->GetPosition();
			_float3& blockPos = pTransformComponent->GetPosition();

			if (col->GetName() == L"Player") // 플레이어와 충돌했다면
			{
				// 만약 빨간블럭이 이동이 끝나지 않았다면
				if (pTransformComponent->GetPosition() != m_activationPosition)
				{
					// 새로운 플레이어 y = 블럭의 y + (플레이어의 높이) + (블럭의 높이 / 2)
					colPos.y = blockPos.y + (pColTransformComponent->GetScale().y) + (pTransformComponent->GetScale().y * 0.5f);
				}
			}
			//else if (col->GetObjectKey() == L"GreenBlock") // 초록블럭과 충돌했다면
			//{
			//	_float3& colPos = col->GetComponent<Engine::CTransformComponent>()->GetPosition();
			//	_float3& blockPos = pTransformComponent->GetPosition();

			//	// 만약 빨간블럭이 이동이 끝나지 않았다면
			//	if (pTransformComponent->GetPosition() != m_activationPosition)
			//	{
			//		//// 새로운 초록블럭 y = 블럭의 y + (초록블럭의 높이 / 2) + (블럭의 높이 / 2)
			//		colPos.y = blockPos.y + (pColTransformComponent->GetScale().y * 0.5f) + (pTransformComponent->GetScale().y * 0.5f);
			//	}
			//}
		}
	}

	pTransformComponent->Lerp(pTransformComponent->GetPosition(), m_activationPosition, 1);

	if (0 == m_activatedLv)
		return;

	if (m_isInteractBlockWithRBtn)
	{
		--m_activatedLv;
		m_activationPosition += GetDirectionOfMovement(FLOAT3_DOWN, pTransformComponent->GetRotation());
		m_isInteractBlockWithRBtn = false;
	}
}

_float3 CRedBlockComponent::GetDirectionOfMovement(_float3 vAt, _float3 vRotation)
{
	_float3 vOut = {};
	_mat rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, vRotation.y, vRotation.x, vRotation.z);
	D3DXVec3TransformCoord(&vOut, &vAt, &rotate);

	return vOut;
}

_bool CRedBlockComponent::CheckBlocksForRayCollision(_float3 direction)
{
	_float3 rayPos = m_pOwner->GetComponent<Engine::CTransformComponent>()->GetPosition();
	_float3 rayDir = direction;
	Engine::CGameObject* eventBlock = nullptr;

	if (Engine::CInputManager::GetInstance()->RayCast(rayPos, rayDir, 1.1f, L"NormalBlock"))
	{
		return true;
	}
	else if (eventBlock = Engine::CInputManager::GetInstance()->RayCast(rayPos, rayDir, 1.1f, L"EventBlock"))
	{
		if (L"GreenBlock" == eventBlock->GetObjectKey())
		{
			return false;
		}

		return true;
	}

	return false;
}