#include "stdafx.h"
#include "Door.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ColliderManager.h"
#include "SoundManager.h"

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
}

SHARED(Engine::CComponent) CDoor::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CDoor) pClone(new CDoor);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CDoor::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;
}

void CDoor::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);

	if (GetOwner()->GetComponent<Engine::CTransformComponent>()->GetRotation().y == 90)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"WhiteBlock", true);
				_float3 pos;
				if (i == 0 && j == 1)
				{
					pos = _float3(GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x - (0.3f),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y + (1 * j),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z);
					pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(0.5f, 1, 1));

				}
				else if (i == 1 && j == 1)
				{
					pos = _float3(GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x + (0.7f),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y + (1 * j),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z);
					pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(1.5f, 1, 1));
				}
				else
				{
					pos = _float3(GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x + (1 * i),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y + (1 * j),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z);
				}

				pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(pos);
				m_pQube.emplace_back(pObj.get());
			}
		}
	}
	else
	{
		for (int i = 0; i < 2; i++) 
		{
			for (int j = 0; j < 3; j++)
			{
				SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"WhiteBlock", true);
				_float3 pos;
				if (i == 0 && j == 1)
				{
					pos = _float3(GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x,
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y + (1 * j),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z - (0.3f));
					pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(1, 1, 0.5f));
				}
				else if (i == 1 && j == 1)
				{
					pos = _float3(GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x,
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y + (1 * j),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z + (0.7f));
					pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(1, 1, 1.5f));
				}
				else
				{
					pos = _float3(GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x,
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y + (1 * j),
						GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z + (1 * i));
				}



				pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(pos);

				m_pQube.emplace_back(pObj.get());
			}
		}
	}
}

_uint CDoor::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	if (!m_enalbe)
		return NO_EVENT;

	if (!m_activation)
	{
		std::vector<Engine::CGameObject*> returnGameObject;

		bool crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(GetOwner()->GetComponent<Engine::CColliderComponent>(), returnGameObject);

		for (auto gameObject : returnGameObject)
		{
			if (gameObject->GetName() == L"Player")
			{
				m_activation = true;
				Engine::CSoundManager::GetInstance()->StartSound(L"OpenDoor.wav", Engine::CHANNELID::DOOR);
			}
		}
	}

	return _uint();
}

_uint CDoor::Update(SHARED(Engine::CComponent) spThis)
{
	if (!m_enalbe)
		return NO_EVENT;

	if (m_activation && m_timer <= m_endTime)
	{
		m_timer += GET_DT;
		DoorActivation();
	}
	return _uint();
}

_uint CDoor::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	return _uint();
}

void CDoor::OnDestroy(void)
{
}

void CDoor::OnEnable(void)
{
}

void CDoor::OnDisable(void)
{
}

void CDoor::DoorActivation()
{
	if (GetOwner()->GetComponent<Engine::CTransformComponent>()->GetRotation().y == 90)
	{
		int i = 0;
		for (auto gameObject : m_pQube)
		{
			if (i < 3)
				gameObject->GetComponent<Engine::CTransformComponent>()->Translate(FLOAT3_LEFT * 5);
			else
				gameObject->GetComponent<Engine::CTransformComponent>()->Translate(FLOAT3_RIGHT * 5);
			i++;
		}
	}
	else
	{
		int i = 0;
		for (auto gameObject : m_pQube)
		{
			if (i < 3)
				gameObject->GetComponent<Engine::CTransformComponent>()->Translate(FLOAT3_BACK * 5);
			else
				gameObject->GetComponent<Engine::CTransformComponent>()->Translate(FLOAT3_FORWARD * 5);
			i++;
		}
	}
}
