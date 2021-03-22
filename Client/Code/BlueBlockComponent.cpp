#include "stdafx.h"
#include "BlueBlockComponent.h"
#include "GameObject.h"
#include "ColliderManager.h"
#include "DataStore.h"
#include "SoundManager.h"

CBlueBlockComponent::CBlueBlockComponent()
{
}


CBlueBlockComponent::~CBlueBlockComponent()
{
}

SHARED(Engine::CComponent) CBlueBlockComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CBlueBlockComponent) pClone(new CBlueBlockComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CBlueBlockComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
	m_pOwner->SetObjectKey(L"BlueBlock");


	std::wstring sectionKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();
	
	m_force = _float3(0, 7, 0);
	Engine::GET_VALUE(true, sectionKey, objectKey, L"m_activatedLv", m_activatedLv);
	Engine::GET_VALUE(true, sectionKey, objectKey, L"m_maxActivatedLv", m_maxActivatedLv);
	Engine::GET_VALUE(true, sectionKey, objectKey, L"m_speed", m_speed);

}

void CBlueBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	pTransformComponent = m_pOwner->GetComponent<Engine::CTransformComponent>();
	m_initialPosition = pTransformComponent->GetPosition();
	m_activationPosition = m_initialPosition;

	_mat rotate;
	m_up = FLOAT3_UP;

	D3DXMatrixRotationYawPitchRoll(&rotate, 
								   D3DXToRadian(pTransformComponent->GetRotation().y), 
								   D3DXToRadian(pTransformComponent->GetRotation().x), 
								   D3DXToRadian(pTransformComponent->GetRotation().z));


	D3DXVec3TransformCoord(&m_up, &m_up, &rotate);
	D3DXVec3TransformCoord(&m_force, &m_force, &rotate);

	
}

_uint CBlueBlockComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CBlueBlockComponent::Update(SHARED(Engine::CComponent) spThis)
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

_uint CBlueBlockComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CBlueBlockComponent::OnDestroy(void)
{
}

void CBlueBlockComponent::OnEnable(void)
{
}

void CBlueBlockComponent::OnDisable(void)
{
}

void CBlueBlockComponent::LClicked()
{
	pTransformComponent->Lerp(pTransformComponent->GetPosition(), m_activationPosition, 1);
	std::vector<Engine::CGameObject*> returnCollider;
	
	bool crushCheck = false;
	SHARED(Engine::CColliderComponent) pCC = m_pOwner->GetComponent<Engine::CColliderComponent>();

	if (m_pPlayer &&
		m_pPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().y > pTransformComponent->GetPosition().y + 5.f)
	{
		m_reload = false;
		m_lButton = false;
		m_rButton = true;
		m_pPlayer = nullptr;
		return;
	}

	if (!m_reload &&
		m_pPlayer &&
		(1 == m_activatedLv) &&
		(m_initialPosition == pTransformComponent->GetPosition()))
	{
		m_reload = true;
	}

	if(pCC->GetIsStarted())
		crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(pCC, returnCollider);

	if (crushCheck) // 충돌시 플레이어 날리고 L끄고 R키고
	{
		for (auto& col : returnCollider)
		{
			if (col->GetName() == L"Player" || col->GetObjectKey() == L"GreenBlock")
			{
				m_pPlayer = col;

				if (m_reload)
				{
					col->GetComponent<Engine::CRigidBodyComponent>()->SetForce(m_force);
					Engine::CSoundManager::GetInstance()->StartSound(L"BoxPush.wav", Engine::CHANNELID::BOX);
				}

				if (0 == m_activatedLv)
				{
					m_isInteractBlockWithLBtn = false;
					break;
				}

				--m_activatedLv;
				m_activationPosition += GetDirectionOfMovement(FLOAT3_UP, pTransformComponent->GetRotation());
				break;
			}
		}
	}


	if (m_maxActivatedLv == m_activatedLv)
		return;

	if (m_isInteractBlockWithLBtn)
	{
		++m_activatedLv;
		m_activationPosition += GetDirectionOfMovement(FLOAT3_DOWN, pTransformComponent->GetRotation());
		m_isInteractBlockWithLBtn = false;
	}
}

void CBlueBlockComponent::RClicked()
{
	auto& pTransformComponent = m_pOwner->GetComponent<Engine::CTransformComponent>();
	pTransformComponent->Lerp(pTransformComponent->GetPosition(), m_activationPosition, 1);

	if (0 == m_activatedLv)
		return;

	if (m_isInteractBlockWithRBtn)
	{
		--m_activatedLv;
		m_activationPosition += GetDirectionOfMovement(FLOAT3_UP, pTransformComponent->GetRotation());

		m_isInteractBlockWithRBtn = false;
		m_rButton = false;
		m_lButton = true;
		m_reload = false;
	}
}

_float3 CBlueBlockComponent::GetDirectionOfMovement(_float3 vAt, _float3 vRotation)
{
	_float3 vOut = {};
	_mat rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, vRotation.y, vRotation.x, vRotation.z);
	D3DXVec3TransformCoord(&vOut, &vAt, &rotate);

	return vOut;
}
