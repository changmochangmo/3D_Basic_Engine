#include "stdafx.h"
#include "BlueBlock.h"
#include "GameObject.h"
#include "ColliderManager.h"

CBlueBlock::CBlueBlock()
{
}


CBlueBlock::~CBlueBlock()
{
}

CBlueBlock* CBlueBlock::Create(_float3 force)
{
	CBlueBlock* block = new CBlueBlock();
	block->m_force = force;

	return block;
}

void CBlueBlock::Awake()
{
}

void CBlueBlock::Start()
{
	m_initialPosition = GetTransformComponent()->GetPosition();
	m_activationPosition = m_initialPosition;

	_mat rotate;
	_float3 up = FLOAT3_UP;

	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(GetTransformComponent()->GetRotation().y), D3DXToRadian(GetTransformComponent()->GetRotation().x), D3DXToRadian(GetTransformComponent()->GetRotation().z));
	D3DXVec3TransformCoord(&up, &up, &rotate);
	D3DXVec3TransformCoord(&m_force, &m_force, &rotate);
	
	m_activationPosition += up;
}

void CBlueBlock::LClicked() // 파란블럭 내리기
{
	std::vector<Engine::CGameObject*> returnCollider;
	bool crushCheck = Engine::CColliderManager::GetInstance()->OnColliderEnter(GetGameObject()->GetComponent<Engine::CColliderComponent>(), returnCollider);

	if (crushCheck) // 충돌시 플레이어 날리고 L끄고 R키고
	{
		m_pEventBlockComponent->SetLButton(false);
		m_pEventBlockComponent->SetRButton(true);
		returnCollider[0]->GetComponent<Engine::CRigidBodyComponent>()->AddForce(m_force * GET_DT);
	}

	m_pTransformComponent->Lerp(m_pTransformComponent->GetPosition(), m_initialPosition, GET_DT * 30);
}

void CBlueBlock::RClicked() // 파란 블럭 올리기
{
	// 올려야함
	m_pTransformComponent->Lerp(m_pTransformComponent->GetPosition(), m_activationPosition,GET_DT * 30);
}

