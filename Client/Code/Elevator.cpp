#include "stdafx.h"
#include "Elevator.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ColliderManager.h"


CElevator::CElevator()
{
}


CElevator::~CElevator()
{
}

SHARED(Engine::CComponent) CElevator::MakeClone(Engine::CGameObject * pObject)
{
	SHARED(CElevator) pClone(new CElevator);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CElevator::Awake(void)
{
	__super::Awake();
	m_componentID = (int)m_s_componentID;

}

void CElevator::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition
			(_float3(
				GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().x - (m_width * 0.5f) + (j * 1),
				GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().y,
				GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition().z - (m_height * 0.5f) + (i * 1))
			);

			m_pQube.emplace_back(pObj.get());
			_float3 temp = pObj->GetComponent<Engine::CTransformComponent>()->GetPosition();
			temp.y -= m_downDepth;
			m_vGoalPos.emplace_back(temp);
		}
	}

	_float3 temp = GetOwner()->GetComponent<Engine::CTransformComponent>()->GetPosition();
	temp.y -= m_downDepth;
	m_pQube.emplace_back(GetOwner());
	m_vGoalPos.emplace_back(temp);
}

_uint CElevator::FixedUpdate(SHARED(Engine::CComponent) spThis)
{
	if(m_end)
		return _uint();

	if (!m_activation)
	{
		std::vector<Engine::CGameObject*> returnGameObject;
		bool crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(GetOwner()->GetComponent<Engine::CColliderComponent>(), returnGameObject);

		for (auto gameObject : returnGameObject)
		{
			if (gameObject->GetName() == L"Player")
			{
				m_activation = true;
				m_playerObj = gameObject;
			}
		}
	}

	return _uint();
}

_uint CElevator::Update(SHARED(Engine::CComponent) spThis)
{
	if (m_end)
		return _uint();

	if (m_activation)
	{
		ElevatorActivation();
	}
	return _uint();
}

_uint CElevator::LateUpdate(SHARED(Engine::CComponent) spThis)
{
	if (m_end)
		return _uint();

	return _uint();
}

void CElevator::OnDestroy(void)
{
}

void CElevator::OnEnable(void)
{
}

void CElevator::OnDisable(void)
{
}

void CElevator::Init(_int width, _int height, _int downDepth)
{
	m_width = width;
	m_height = height;
	m_downDepth = downDepth;
}

void CElevator::ElevatorActivation()
{
	int i = 0;
	for (auto gameObject : m_pQube)
	{
		_float3& curPos = gameObject->GetComponent<Engine::CTransformComponent>()->GetPosition();
		_float3 goalPos = m_vGoalPos[i];
		gameObject->GetComponent<Engine::CTransformComponent>()->Lerp(curPos, goalPos, 30 * GET_DT);
		m_playerObj->GetComponent<Engine::CTransformComponent>()->SetPositionY(gameObject->GetComponent<Engine::CTransformComponent>()->GetPosition().y + 2.0f);
		i++;
	}

	_float3 pos1 = m_pQube[m_pQube.size() - 1]->GetComponent<Engine::CTransformComponent>()->GetPosition();
	_float3 pos2 = m_vGoalPos[m_vGoalPos.size() - 1];
	if (Engine::Distance(pos1, pos2) <= 0.4f)
	{
		m_end = true;
	}
}
