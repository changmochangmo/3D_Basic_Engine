#include "stdafx.h"
#include "StairsComponent.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ColliderManager.h"

CStairsComponent::CStairsComponent()
{
}


CStairsComponent::~CStairsComponent()
{
}

SHARED(Engine::CComponent) CStairsComponent::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CStairsComponent) pClone(new CStairsComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CStairsComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
	m_pOwner->SetLayerKey(L"Stairs");
	m_pOwner->SetObjectKey(L"Stairs");
}

void CStairsComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);

	// 계단생성하기
	// height 1당 블럭은 4개

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition
			(_float3(
				GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x - (m_width * 0.5f) + (j * 1),
				GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y,
				GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z - (m_height * 0.5f) + (i * 1))
			);

			m_pStairs.emplace_back(pObj);
			m_vCurPos.emplace_back(pObj->GetComponent<Engine::CTransformComponent>()->GetPosition());
		}
	}

}

_uint CStairsComponent::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	if (m_activation)
	{
		for (auto gameObject : m_pStairs)
		{
			std::vector<Engine::CGameObject*> returnGameObject;
  			bool crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(gameObject->GetComponent<Engine::CColliderComponent>(), returnGameObject);

			if (crushCheck)
			{
				for (auto col : returnGameObject)
				{
					if (col->GetName() == L"Player")
					{
						col->GetComponent<Engine::CTransformComponent>()->AddPositionY(0.01f);
					}
				}
			}
		}
	}

	if (!m_activation)
	{
		std::vector<Engine::CGameObject*> returnGameObject;

		bool crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(GetOwner()->GetComponent<Engine::CColliderComponent>(), returnGameObject);

		for (auto gameObject : returnGameObject)
		{
			if (gameObject->GetName() == L"Player")
			{
				m_activation = true;

				for (auto gameObject : m_pStairs)
				{
					gameObject->GetComponent<Engine::CColliderComponent>()->SetColliderID(5);
				}
			}
		}
	}
	return _uint();
}

_uint CStairsComponent::Update(SHARED(Engine::CComponent) spThis)
{
	if (m_activation && m_stairsActivation)
	{
		StairsActivation();
	}
	return _uint();
}

_uint CStairsComponent::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CStairsComponent::OnDestroy(void)
{
}

void CStairsComponent::OnEnable(void)
{
}

void CStairsComponent::OnDisable(void)
{
}

void CStairsComponent::Init(_int width, _int height)
{
	m_width = width;
	m_height = height * 4;
}
void CStairsComponent::StairsActivation()
{
	int i = 0;
	for (auto gameObject : m_pStairs)
	{
		_float3& curPos = gameObject->GetComponent<Engine::CTransformComponent>()->GetPosition();
		_float3 upPos = m_vCurPos[i];
		upPos.y += 1.0f - (0.25f * (i / m_width));
		gameObject->GetComponent<Engine::CTransformComponent>()->Lerp(curPos, upPos, 30 * GET_DT);
		i++;
	}
}

/*
각도
앞
(i / m_width)
오른쪽
(i % m_width)

*/