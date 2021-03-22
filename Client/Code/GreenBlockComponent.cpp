#include "stdafx.h"
#include "GreenBlockComponent.h"
#include "GameObject.h"
#include "ColliderManager.h"
#include "DataStore.h"
#include "InputManager.h"
#include "RedBlockComponent.h"

CGreenBlockComponent::CGreenBlockComponent()
{
}


CGreenBlockComponent::~CGreenBlockComponent()
{
}

SHARED(Engine::CComponent) CGreenBlockComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CGreenBlockComponent) pClone(new CGreenBlockComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CGreenBlockComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
	m_pOwner->SetObjectKey(L"GreenBlock");

	std::wstring sectionKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();
}

void CGreenBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	auto& pTransformComponent = m_pOwner->GetComponent<Engine::CTransformComponent>();
	m_initialPosition = pTransformComponent->GetPosition();
	m_activationPosition = m_initialPosition;
	pTransformComponent->SetScale(_float3(0.8f, 0.8f, 0.8f));
	//pTransformComponent->SetScale(_float3(1.f, 1.f, 1.f));

	if (auto& pCC = m_pOwner->GetComponent<Engine::CColliderComponent>())
		pCC->SetColliderID((_int)EColliderID::Player);
}

_uint CGreenBlockComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CGreenBlockComponent::Update(SHARED(Engine::CComponent) spThis)
{
	std::vector<Engine::CGameObject*> returnCollider;
	bool crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(m_pOwner->GetComponent<Engine::CColliderComponent>(), returnCollider);
	
	if (crushCheck && !m_curCollidedBlock)
	{
		for (auto& col : returnCollider)
		{
			if (col->GetLayerKey() == L"EventBlock")
			{
				m_curCollidedBlock = col;
			}
		}
	}
	
	if (m_curCollidedBlock)
	{
		auto& pGreenBlockTransformComponent = m_pOwner->GetComponent<Engine::CTransformComponent>();
		auto& pColTransformComponent = m_curCollidedBlock->GetComponent<Engine::CTransformComponent>();

		_float3& GreenBlockPos = pGreenBlockTransformComponent->GetPosition();
		_float3& colPos = pColTransformComponent->GetPosition();

		// 만약 빨간블럭이 이동이 끝나지 않았다면
		if (colPos != m_curCollidedBlock->GetComponent<CRedBlockComponent>()->GetActivationPosition())
		{
			//// 새로운 초록블럭 y = 블럭의 y + (초록블럭의 높이 / 2) + (블럭의 높이 / 2)
			//colPos.y = blockPos.y + (pColTransformComponent->GetScale().y * 0.5f) + (pTransformComponent->GetScale().y * 0.5f);

			_float3 nextGreenBlockPos = GreenBlockPos + GetDirectionOfMovement(FLOAT3_UP, pColTransformComponent->GetRotation());
			pGreenBlockTransformComponent->Lerp(GreenBlockPos, nextGreenBlockPos, 1);
		}
		// 이동이 끝났다면
		else
		{
			m_curCollidedBlock = nullptr;
		}
	}
	

	return _uint();
}

_uint CGreenBlockComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CGreenBlockComponent::OnDestroy(void)
{
}

void CGreenBlockComponent::OnEnable(void)
{
}

void CGreenBlockComponent::OnDisable(void)
{
}

void CGreenBlockComponent::LClicked()
{
}

void CGreenBlockComponent::RClicked()
{
}

Engine::CGameObject* CGreenBlockComponent::CheckBlocksForRayCollision(_float3 direction)
{
	_float3 rayPos = m_pOwner->GetComponent<Engine::CTransformComponent>()->GetPosition();
	_float3 playerDir = GetBlockDir(direction);
	_float rayDistance = 0.3f;
	Engine::CGameObject* targetBlock = nullptr;

	if (targetBlock = Engine::CInputManager::GetInstance()->RayCast(rayPos, playerDir, rayDistance, L"NormalBlock"))
	{
		return targetBlock;
	}
	else if (targetBlock = Engine::CInputManager::GetInstance()->RayCast(rayPos, playerDir, rayDistance, L"EventBlock"))
	{
		return targetBlock;
	}

	return nullptr;
}

_float3 CGreenBlockComponent::GetBlockDir(_float3 dir)
{
	_float3 blockDir = dir;
	_float3 blockRotation = m_pOwner->GetComponent<Engine::CTransformComponent>()->GetRotation();
	_mat rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(blockRotation.y), D3DXToRadian(blockRotation.x), D3DXToRadian(blockRotation.z));
	D3DXVec3TransformCoord(&blockDir, &blockDir, &rotate);

	return blockDir;
}

_float3 CGreenBlockComponent::GetDirectionOfMovement(_float3 vAt, _float3 vRotation)
{
	_float3 vOut = {};
	_mat rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, vRotation.y, vRotation.x, vRotation.z);
	D3DXVec3TransformCoord(&vOut, &vAt, &rotate);

	return vOut;
}
