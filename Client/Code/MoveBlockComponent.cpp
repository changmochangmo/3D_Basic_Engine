#include "stdafx.h"
#include "MoveBlockComponent.h"
#include "GameObject.h"
#include "ColliderManager.h"
#include "DataStore.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "ObjectFactory.h"

CMoveBlockComponent::CMoveBlockComponent()
{
}


CMoveBlockComponent::~CMoveBlockComponent()
{
}

SHARED(Engine::CComponent) CMoveBlockComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CMoveBlockComponent) pClone(new CMoveBlockComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CMoveBlockComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
	m_pOwner->SetObjectKey(L"MoveBlock");


	std::wstring sectionKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();
}

void CMoveBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);

	m_moveDir[0] = FLOAT3_FORWARD;
	m_moveDir[1] = FLOAT3_RIGHT;
	m_moveDir[2] = FLOAT3_BACK;
	m_moveDir[3] = FLOAT3_LEFT;
	m_moveType = 0;

	m_oldPos = GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition();

	{
		m_pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		m_pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1, 1, -1));
		m_pObj->GetComponent<Engine::CTransformComponent>()->AddRotationY(90);
		m_pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CAabbCollider::Create(FLOAT3_ONE, _float3(0,0,2)));
		m_pObj->GetComponent<Engine::CColliderComponent>()->SetColliderID(5);
		m_pObj->AddComponent<CDoor>()->SetEnable(false);
	}
}

_uint CMoveBlockComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	if (!m_enalbe)
		return NO_EVENT;

	return _uint();
}

_uint CMoveBlockComponent::Update(SHARED(Engine::CComponent) spThis)
{
	if (!m_enalbe)
		return NO_EVENT;

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

_uint CMoveBlockComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	if (!m_enalbe)
		return NO_EVENT;

	return _uint();
}

void CMoveBlockComponent::OnDestroy(void)
{
}

void CMoveBlockComponent::OnEnable(void)
{
}

void CMoveBlockComponent::OnDisable(void)
{
}

void CMoveBlockComponent::LClicked()
{
	SHARED(Engine::CTransformComponent) transform = GetOwner()->GetComponent<Engine::CTransformComponent>();
	transform->AddPosition(m_moveDir[m_moveType] * GET_DT);

	if (Engine::Distance(transform->GetPosition(), m_goalPos) <= 0.1f)
	{
		m_pObj->GetComponent<CDoor>()->SetEnable(true);
		transform->SetPosition(m_goalPos);
		m_enalbe = false;
	}

	// raycast È®ÀÎ
	if (Engine::CInputManager::GetInstance()->RayCast(transform->GetPosition(), m_moveDir[m_moveType], transform->GetScale().x * 0.5f, L"EventBlock"))
	{
		++m_moveType;
		if (m_moveType == 4)
		{
			m_moveType = 0;
		}
	}
	
}

void CMoveBlockComponent::RClicked()
{
	if (m_isInteractBlockWithRBtn)
	{
		m_isInteractBlockWithRBtn = false;
		GetOwner()->GetComponent<Engine::CTransformComponent>()->SetPosition(m_oldPos);
		m_moveType = 0;
		m_lButton = true;
		m_rButton = false;
	}
}
