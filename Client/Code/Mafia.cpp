#include "stdafx.h"
#include "Mafia.h"
#include "SceneManager.h"
#include "FRC.h"
#include "DynamicMesh.h"
#include "TextManager.h"

_uint CMafia::m_s_uniqueID = 0;

CMafia::CMafia()
{
}


CMafia::~CMafia()
{
	OnDestroy();
}

SP(CMafia) CMafia::Create(_bool isStatic)
{
	SP(CMafia) spInstance(new CMafia, Engine::SmartDeleter<CMafia>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMafia::MakeClone(void)
{
	SP(CMafia) spClone(new CMafia, Engine::SmartDeleter<CMafia>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spFadeInOut	= spClone->GetComponent<Engine::CFadeInOutC>();

	return spClone;
}

void CMafia::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Enemy;
	m_dataID	= (_int)EDataID::Enemy;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();
	m_spFadeInOut	= AddComponent<Engine::CFadeInOutC>();

	m_spFadeInOut->SetIsFadeIn(false);
	m_spFadeInOut->SetSpeed(1.f);
	m_spFadeInOut->SetIsEnabled(false);

	m_spTransform->SetSize(_float3(0.01f, 0.01f, 0.01f));
	m_spTransform->SetRotationY(PI);
}

void CMafia::Start(void)
{
	__super::Start();
	m_pPlayerTransform = Engine::GET_CUR_SCENE->FindObjectWithKey(L"Player")->GetTransform().get();
	AddComponent<Engine::CDebugC>();
}

void CMafia::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMafia::Update(void)
{
	__super::Update();
	
}

void CMafia::LateUpdate(void)
{
	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();
	Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[0]);

	_float deltaTime = GET_DT;
	if (m_onGround)
	{
		m_spRigidBody->AddForce(-GRAVITY * m_spRigidBody->GetGravityConstant());
	}

	if (m_fightAble)
	{
		_float3 dir = m_pPlayerTransform->GetPosition() - m_spTransform->GetPosition();
		dir.y = 0;
		D3DXVec3Normalize(&dir, &dir);

		if (m_isHurt)
		{
			m_status = STATUS_HURT;
		}
		
		switch (m_status)
		{
		case STATUS_IDLE:
		{
			if (D3DXVec3Length(&(m_spTransform->GetPosition() - m_pPlayerTransform->GetPosition())) < 5)
				m_status = STATUS_MOVE;

			break;
		}

		case STATUS_MOVE:
		{
			
			m_spTransform->SetForward(dir);
			m_spTransform->AddPosition(dir * 2 * deltaTime);
			if (D3DXVec3Length(&(m_spTransform->GetPosition() - m_pPlayerTransform->GetPosition())) < 1)
				m_status = STATUS_ATTACK;

			break;
		}

		case STATUS_ATTACK:
		{
			if (m_aniIndex == ANI_ATTACK && pDM->IsAnimationEnd())
				m_status = STATUS_IDLE;

			m_spTransform->AddPosition(dir * deltaTime);
			break;
		}

		case STATUS_HURT:
			if (m_lastStatus != STATUS_HURT)
			{
				m_spTransform->AddPosition(-dir * 30 * deltaTime);
				--m_hp;
			}

			if (m_redTimer <= 0.f)
			{
				m_spGraphics->m_mtrl.Diffuse.g = 0;
				m_spGraphics->m_mtrl.Diffuse.b = 0;
				m_redTimer = 0.1f;
			}
			else
			{
				m_spGraphics->m_mtrl.Diffuse.g = 1;
				m_spGraphics->m_mtrl.Diffuse.b = 1;
			}

			if (m_hurtTimer < 0)
			{
				m_status = STATUS_IDLE;
				m_spGraphics->m_mtrl.Diffuse.g = 1;
				m_spGraphics->m_mtrl.Diffuse.b = 1;
				m_hurtTimer = .5f;
				m_redTimer = 0.f;
			}
			m_isHurt = false;
			m_hurtTimer -= GET_DT;
			m_redTimer -= GET_DT;
			break;
		}
	}

	if (m_hp <= 0)
	{
		m_spGraphics->m_mtrl.Diffuse.g = 1;
		m_spGraphics->m_mtrl.Diffuse.b = 1;

		m_status = STATUS_DYING;
		m_aniIndex = ANI_IDLE;
		m_spTransform->SetGoalForward(UP_VECTOR);
		m_spTransform->SetSlerpOn(true);
		m_spFadeInOut->SetIsEnabled(true);
		if (m_spFadeInOut->GetFinish())
			m_deleteThis = true;
	}
	
	
	UpdateAnimation();
	m_lastStatus = m_status;
	m_onGround = false;
	__super::LateUpdate();
}

void CMafia::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CMafia::OnEnable(void)
{
	__super::OnEnable();
	
}

void CMafia::OnDisable(void)
{
	__super::OnDisable();
	
}

void CMafia::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMafia::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.pOtherCollider->GetOwner()->GetCollisionID() == (_int)EColliderID::Map)
	{
		if (ci.normal.y < -0.7)
		{
			m_onGround = true;
			m_spRigidBody->SetVelocityY(0);
		}
	}

	else if (ci.pOtherCollider->GetOwner()->GetCollisionID() == (_int)EColliderID::PlayerRay)
	{
		if (ci.normal.y > 0.5)
		{
			m_isHurt = true;
			SP(Engine::CRigidBodyC) spOtherRigid = ci.pOtherCollider->GetOwner()->GetRigidbody();
			if (spOtherRigid != nullptr)
				spOtherRigid->AddForce(_float3(0, 300, 0));
		}
	}
}

void CMafia::OnCollisionStay(Engine::_CollisionInfo ci)
{
	if (ci.normal.y < -0.7)
	{
		m_onGround = true;
	}
}

void CMafia::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CMafia::UpdateAnimation(void)
{
	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();
	Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[0]);

	if (m_lastStatus != m_status || pDM->IsAnimationEnd())
	{
		_float	aniSpeed = 1.f;
		_bool	fixTillEnd = false;
		_double smoothTime = 0.25;
		_float	changeWeight = 0.9f;
		_bool	replay = true;
		switch (m_status)
		{
		case STATUS_IDLE:
			m_aniIndex = ANI_IDLE;
			smoothTime = 0.25;
			break;

			//case STATUS_WALK:
			//	m_aniIndex = ANI_RUN;
			//	aniSpeed = 2.f;
			//	break;
			//
			//case STATUS_RUN:
			//	m_aniIndex = ANI_RUN;
			//	aniSpeed = 3.f;
			//	break;

		case STATUS_MOVE:
			m_aniIndex = ANI_MOVE;
			aniSpeed = 3.f;
			break;

		case STATUS_HURT:
			m_aniIndex = ANI_HURT;
			aniSpeed = 5.f;
			break;

		case STATUS_ATTACK:
				m_aniIndex = ANI_ATTACK;
				aniSpeed = 1.9f;
			break;
		}

		pDM->ChangeAniSet(m_aniIndex, fixTillEnd, smoothTime, changeWeight);
		pDM->GetAniCtrl()->SetSpeed(aniSpeed);
		pDM->GetAniCtrl()->SetReplay(replay);
	}
}
