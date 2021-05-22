#include "stdafx.h"
#include "Boss.h"
#include "TextManager.h"
#include "InputManager.h"
#include "FRC.h"
#include "DynamicMesh.h"
#include "SceneManager.h"
#include "ObjectFactory.h"

#include "RollerBlade.h"
#include "SandBag.h"
#include "MafiaBall.h"
_uint CBoss::m_s_uniqueID = 0;

CBoss::CBoss()
{
}


CBoss::~CBoss()
{
	OnDestroy();
}

SP(CBoss) CBoss::Create(_bool isStatic)
{
	SP(CBoss) spInstance(new CBoss, Engine::SmartDeleter<CBoss>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBoss::MakeClone(void)
{
	SP(CBoss) spClone(new CBoss, Engine::SmartDeleter<CBoss>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();

	return spClone;
}

void CBoss::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Enemy;
	m_dataID	= (_int)EDataID::Enemy;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();

	m_spTransform->SetSize(_float3(0.01f, 0.01f, 0.01f));
	m_spTransform->SetRotationY(PI);
}

void CBoss::Start(void)
{
	__super::Start();
	m_spTransform->SetPosition(-7.7f, 2.25f, 70.f);
	m_pPlayerTransform = Engine::GET_CUR_SCENE->FindObjectWithKey(L"Player")->GetTransform().get();
	//m_spRigidBody->SetUseGravity(false);

	m_pLeftRoller = std::dynamic_pointer_cast<CRollerBlade>(Engine::ADD_CLONE(L"RollerBlade", Engine::GET_CUR_SCENE, false)).get();
	m_pLeftRoller->SetBoss(this);
	m_pLeftRoller->SetIsRightHand(false);
	m_pLeftRoller->SetIsEnabled(false);

	m_pRightRoller = std::dynamic_pointer_cast<CRollerBlade>(Engine::ADD_CLONE(L"RollerBlade", Engine::GET_CUR_SCENE, false)).get();
	m_pRightRoller->SetBoss(this);
	m_pRightRoller->SetIsEnabled(false);
	m_pRightRoller->SetIsHoming(true);

	for (_int i = 0; i < 20; ++i)
	{
		CRollerBlade* pRoller =
			std::dynamic_pointer_cast<CRollerBlade>(Engine::ADD_CLONE(L"RollerBlade", Engine::GET_CUR_SCENE, false)).get();

		pRoller->SetBoss(this);
		pRoller->SetIsEnabled(false);
		pRoller->SetIsOnHand(false);
		pRoller->SetIsEnabled(false);

		m_vRoller.emplace_back(pRoller);
	}

	for (_int i = 0; i < 5; ++i)
	{
		CRollerBlade* pRoller =
			std::dynamic_pointer_cast<CRollerBlade>(Engine::ADD_CLONE(L"RollerBlade", Engine::GET_CUR_SCENE, false)).get();

		pRoller->SetBoss(this);
		pRoller->SetIsEnabled(false);
		pRoller->SetIsOnHand(false);
		pRoller->SetIsEnabled(false);
		pRoller->SetIsHoming(true);

		m_vChargeRoller.emplace_back(pRoller);
	}

	for (_int i = 0; i < 20; ++i)
	{
		CSandBag* pSandBag =
			std::dynamic_pointer_cast<CSandBag>(Engine::ADD_CLONE(L"SandBag", Engine::GET_CUR_SCENE, false)).get();

		pSandBag->SetLaneNumber(i % 10);

		m_vSandBags.emplace_back(pSandBag);
	}

	//m_pMafiaBall = 
	//	std::dynamic_pointer_cast<CMafiaBall>(Engine::ADD_CLONE(L"MafiaBall", false)).get();
	//
	//m_pMafiaBall->GetTransform()->SetPosition(m_spTransform->GetPosition());
}

void CBoss::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBoss::Update(void)
{
	__super::Update();
	
	
	
}

void CBoss::LateUpdate(void)
{
	//m_status = STATUS_IDLE;
	PhaseChange();
	PatternChange();

	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
		m_gotHit = true;

	if (Engine::IMKEY_DOWN(KEY_UP))
	{
		m_gotHit = true;
	}

	if (Engine::IMKEY_DOWN(KEY_RIGHT))
	{
		switch (m_phase)
		{
		case PHASE_ZERO:
			m_status = STATUS_DIZZY;
			Jump(_float3(-7.7f, -1.3f, 65.75f), 1, false, false, 2);
			break;

		case PHASE_ONE:
			break;

		case PHASE_TWO:
			break;

		case PHASE_THREE:
			break;

		default:
			break;
		}

	}


	if (m_onGround)
	{
		m_spRigidBody->AddForce(-GRAVITY * m_spRigidBody->GetGravityConstant());
	}



	

	switch (m_pattern)
	{
	case 0:
		PatternOne();
		break;
	case 1:
		PatternTwo();
		break;

	default:
		break;
	}

	Dizzy();
	Exhausted();
	

	UpdateAnimation();
	
	std::wstring curStateStr;
	CurStatusInStr(curStateStr);
	//Engine::REWRITE_TEXT(L"Test0", curStateStr);
	//Engine::REWRITE_TEXT(L"Test1", std::to_wstring(m_phase));
	//Engine::REWRITE_TEXT(L"Test2", std::to_wstring(m_pattern));

	m_lastStatus = m_status;
	m_onGround = false;
	__super::LateUpdate();
}

void CBoss::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CBoss::OnEnable(void)
{
	__super::OnEnable();
	
}

void CBoss::OnDisable(void)
{
	__super::OnDisable();
	
}

void CBoss::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CBoss::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.pOtherCollider->GetOwner()->GetCollisionID() == (_int)EColliderID::Map)
	{
		if (ci.normal.y < -0.7)
		{
			m_onGround = true;
			m_spRigidBody->SetVelocityY(0);

			if(m_status == STATUS_JUMP)
				JumpDone();
		}
	}

	switch (m_phase)
	{
	case PHASE_ZERO:
		break;

	case PHASE_ONE:
	{
		if (m_pattern == 0)
		{
			_float curVelocityLength = D3DXVec3Length(&m_spRigidBody->GetVelocity());
			if (m_status == STATUS_PATTERN1 && curVelocityLength > 5.f)
			{
				m_status = STATUS_DIZZY;
			}
		}
		break;
	}
	case PHASE_TWO:
		if (m_pattern == 1)
		{
			if (m_status == STATUS_PATTERN2 && m_stompTimer != 0)
			{
				m_status = STATUS_EXHAUSTED;
				
				m_spRigidBody->SetVelocity(ZERO_VECTOR);
				m_spRigidBody->SetForce(ZERO_VECTOR);
				m_spRigidBody->SetGravityConstant(0);
				m_spTransform->SetRotationZ(0);
				m_spTransform->SetForward(_float3(0, 0, -1));
				m_spTransform->SetPositionY(-1.3f);

				m_stompTimer = 0.f;
			}

		}
		break;

	case PHASE_THREE:
		break;

	default:
		break;
	}
}

void CBoss::OnCollisionStay(Engine::_CollisionInfo ci)
{
	if (ci.normal.y < -0.7)
	{
		m_onGround = true;
	}
}

void CBoss::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CBoss::Jump(_float3 goalPos, _float time, _bool phaseChange, _bool patternChange, _float gravityConstant)
{
	if (m_saveStatus == UNDEFINED)
		m_saveStatus = m_status;

	_float3 posDiff = goalPos - m_spTransform->GetPosition();
	m_spRigidBody->SetVelocity(posDiff / time - 0.5f * GRAVITY * gravityConstant * time);
	m_spRigidBody->SetGravityConstant(gravityConstant);
	m_jumpGoalPos = goalPos;

	m_phaseChange	= phaseChange;
	m_patternChange = patternChange;

	m_status = STATUS_JUMP;
}

void CBoss::JumpDone(void)
{
	m_spRigidBody->SetGravityConstant(1.f);
	m_status		= m_saveStatus;
	m_saveStatus	= UNDEFINED;

	m_spTransform->SetPosition(m_jumpGoalPos);
	m_spRigidBody->SetVelocity(ZERO_VECTOR);
}

void CBoss::Dizzy(void)
{
	if (m_dizzyTimer > 0)
		m_status = STATUS_DIZZY;

	if (m_status == STATUS_DIZZY)
	{
		m_dizzyTimer += GET_DT;
	}

	if (m_dizzyTimer >= m_dizzyDuration || m_gotHit)
	{
		m_gotHit = false;
		m_dizzyTimer = 0;
		if (m_pattern == 2)
			m_phaseChange = true;
		else
			m_patternChange = true;
	}

	

}

void CBoss::Exhausted(void)
{
	if (m_exhaustedTimer > 0)
		m_status = STATUS_EXHAUSTED;

	if (m_status == STATUS_EXHAUSTED)
	{
		m_exhaustedTimer += GET_DT;


		if (m_exhaustedTimer >= m_exhaustedDuration || m_gotHit)
		{
			m_gotHit = false;
			m_exhaustedTimer = 0;
			m_initNow = true;

			m_status = STATUS_PATTERN1 + m_pattern;
			m_phaseChange = true;
			//if (m_gotHit)
			//	m_exhaustedHitCount++;
			//
			//if (m_exhaustedHitCount == 3)
			//	m_phaseChange = true;
		}
	}
}

void CBoss::PatternOne(void)
{
	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();
	Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[0]);
	
	if (m_status != STATUS_PATTERN1)
		return;

	switch (m_phase)
	{
	case PHASE_ZERO:
		break;

	case PHASE_ONE:
	{
		m_aniIndex = ANI_SPIN;

		_float3 dir = _float3(m_pPlayerTransform->GetPosition().x - m_spTransform->GetPosition().x, 0, 0);
		D3DXVec3Normalize(&dir, &dir);

		if((dir.x < 0 && m_spRigidBody->GetVelocity().x < 0)
		|| (dir.x > 0 && m_spRigidBody->GetVelocity().x > 0))
			m_spRigidBody->AddForce(dir * 3);
		else
			m_spRigidBody->AddForce(dir * 10);

		break;
	}
	case PHASE_TWO:
	{
		_float deltaTIme = GET_DT;
		if (m_lastStatus == STATUS_PATTERN2)
		{
			m_aniIndex = ANI_ANGRY0;
			break;
		}

		if (m_aniIndex == ANI_ANGRY0 && pDM->IsAnimationEnd())
		{
			m_spTransform->SetForward(FORWARD_VECTOR);
			_float3 underTheStage(-9.f, -2.3f, 60.75f);
			Jump(underTheStage, 1.f, false, false, 1.f);
			break;
		}

		if (m_spTransform->GetPosition().z == 60.75f && m_sandBagTimer == 0.f)
		{
			m_sandBagTimer += deltaTIme;
			m_aniIndex = ANI_BRAVO;
		}

		if (m_sandBagTimer != 0.f && m_sandBagTimer < m_sandBagDuration)
		{
			m_sandBagTimer += deltaTIme;

			if (m_sandBagTimer >= m_sandBagDuration)
			{
				if (m_curWave == m_sandBagWave)
				{
					m_status = STATUS_PATTERN2;
					m_pattern++;
					Jump(_float3(-7.7f, -1.3f, 65.75f), 2.f, false, false);
					break;
				}

				
				m_sandBagExceptLane = rand() % 10;
				for (_int i = (m_curWave % 2) * 10; i < (m_curWave % 2) * 10 + 10; ++i)
				{
					if (i - (m_curWave % 2) * 10 == m_sandBagExceptLane)
						continue;
					m_vSandBags[i]->SetIsEnabled(true);
				}
				
				++m_curWave;

				

				m_sandBagTimer = deltaTIme;
			}
		}


		break;
	}

	case PHASE_THREE:
	{
		_float deltaTIme = GET_DT;
		if (m_lastStatus == STATUS_PATTERN2)
		{
			m_aniIndex = ANI_DEAD;
			break;
		}
		if (m_aniIndex == ANI_DEAD && pDM->IsAnimationEnd())
			m_deleteThis = true;
		//if (m_aniIndex == ANI_ANGRY0 && pDM->IsAnimationEnd())
		//{
		//	m_spRigidBody->SetUseGravity(true);
		//	if (m_spTransform->GetPosition().x < -7.7)
		//		Jump(_float3(-2.7f, -1.3f, 65.75f), 0.5, false, false, 1);
		//	else
		//		Jump(_float3(-12.71f, -1.3f, 65.75f), 0.5, false, false, 1);
		//	break;
		//}
		//else if (m_lastStatus == STATUS_JUMP && m_status == STATUS_PATTERN1)
		//{
		//	m_pMafiaBall->SetIsEnabled(true);
		//}

		break;
	}

	default:
		break;
	}
}

void CBoss::PatternTwo(void)
{
	if (m_status != STATUS_PATTERN2)
		return;

	switch (m_phase)
	{
	case PHASE_ZERO:
		break;

	case PHASE_ONE:
	{
		if (m_gotHit)
		{
			m_pLeftRoller->SetIsEnabled(false);
			m_pRightRoller->SetIsEnabled(false);
			m_phaseChange = true;
			break;
		}

		m_status = STATUS_PATTERN2;
		if (m_lastStatus == STATUS_DIZZY)
		{
			if (m_spTransform->GetPosition().x < -7.7)
				Jump(_float3(-0.7f, -1.3f, 65.75f), 1, false, false, 2);
			else
				Jump(_float3(-15.1f, -1.3f, 65.75f), 1, false, false, 2);
		}

		else if (m_lastStatus == STATUS_JUMP && m_status == STATUS_PATTERN2)
		{
			m_pLeftRoller->SetIsEnabled(true);
			m_pRightRoller->SetIsEnabled(true);

			m_aniIndex = ANI_CHARGE;
		}
		
		if (m_aniIndex == ANI_CHARGE)
		{
			m_chargeTimer += GET_DT;
			if (m_chargeTimer >= m_chargeDuration)
			{
				m_chargeTimer = 0.f;
				m_aniIndex = ANI_THROW;
			}
		}

		if (m_aniIndex == ANI_THROW)
		{
			m_throwTimer += GET_DT;

			if (m_throwTimer > 1.f / m_rollerCoef && m_rollerInHand == 2)
			{
				m_vRoller[m_rollerIndex++]->SetIsEnabled(true);
				m_rollerInHand = 1;
			}

			else if (m_throwTimer > 1.5 / m_rollerCoef && m_rollerInHand == 1)
			{
				m_vRoller[m_rollerIndex++]->SetIsEnabled(true);
				if (m_rollerIndex == 10)
				{
					m_rollerCoef = 2;
				}
				else if (m_rollerIndex == 20)
					m_rollerIndex = 0;

				m_rollerInHand = 2;
				m_throwTimer = 0.f;
			}

			if (m_throwTimer > 0.3f / m_rollerCoef && ((m_rollerIndex % 4) == 3))
			{
				m_vChargeRoller[m_rollerIndex / 4]->SetIsEnabled(true);
			}
		}

		_float3 dir = _float3(-7.7f - m_spTransform->GetPosition().x, 0, 0);
		D3DXVec3Normalize(&dir, &dir);

		m_spTransform->SetForward(dir);

		

		break;
	}
	case PHASE_TWO:
	{
		_float deltaTime = GET_DT;
		if (m_lastStatus != STATUS_PATTERN2 || m_initNow)
		{
			m_spTransform->SetForward(_float3(0, 0, -1));
			m_aniIndex = ANI_IDLE;

			m_spRigidBody->SetUseGravity(false);
			m_initNow = false;
			m_fixedDir = false;
			m_floatingTimer = 0.f;
			m_stompTimer = 0.f;
		}

		if (m_floatingTimer <= m_floatingDuration)
		{
			m_spRigidBody->SetVelocity(ZERO_VECTOR);
			m_spTransform->AddRotationY(2 * PI * deltaTime);
			m_spTransform->AddPositionY(3.f * deltaTime);

			m_floatingTimer += deltaTime;
		}
		else
		{
			_float3 bossToPlayer = m_pPlayerTransform->GetPosition() - m_spTransform->GetPosition();
			m_spTransform->SetRotationY(0);
			if (m_stompTimer <= m_stompDuration)
			{
				D3DXVec3Normalize(&bossToPlayer, &bossToPlayer);
				_float radian = acos(D3DXVec3Dot(&-UP_VECTOR, &bossToPlayer));

				if (bossToPlayer.x < 0)
					radian *= -1;

				m_spTransform->SetRotationZ(radian);
				m_stompTimer += deltaTime;
			}
			else
			{				
				if(m_fixedDir == false)
				{
					m_shootDir = bossToPlayer;
					D3DXVec3Normalize(&m_shootDir, &m_shootDir);
					m_spRigidBody->AddForce(-m_shootDir * 3000);
					m_fixedDir = true;
				}
				else
				{
					m_spRigidBody->AddForce(m_shootDir * 100);
				}
			}
		}

		break;
	}
	case PHASE_THREE:
		break;

	default:
		break;
	}
}


void CBoss::UpdateAnimation(void)
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

		case STATUS_JUMP:
			m_aniIndex = ANI_JUMP;
			aniSpeed = 4.f;
			break;

		case STATUS_DIZZY:
			m_aniIndex = ANI_DIZZY;
			aniSpeed = 1.9f;
			break;
		
		case STATUS_EXHAUSTED:
			m_aniIndex = ANI_DIZZY;
			aniSpeed = 1.9f;
			break;
		}

		switch (m_aniIndex)
		{
		case ANI_THROW:
			smoothTime = 0.45;
			aniSpeed = 1.5f * m_rollerCoef;
			
			//if (pDM->GetAniCtrl()->GetCurIndex() == ANI_THROW && pDM->IsAnimationEnd())
			//{
			//	m_aniIndex = ANI_BRAVO;
			//	smoothTime = 1.f;
			//}
			break;

		case ANI_BRAVO:
			
			break;
		}

		pDM->ChangeAniSet(m_aniIndex, fixTillEnd, smoothTime, changeWeight);
		pDM->GetAniCtrl()->SetSpeed(aniSpeed);
		pDM->GetAniCtrl()->SetReplay(replay);
	}
}

void CBoss::PhaseChange(void)
{
	if (m_phaseChange && m_phase < PHASE_THREE)
	{
		++m_phase;
		m_pattern = 0;

		m_status = STATUS_PATTERN1;

		m_phaseChange = false;
		m_patternChange = false;
	}
}

void CBoss::PatternChange(void)
{
	if (m_patternChange && m_pattern < 1)
	{
		++m_pattern;

		m_status = STATUS_PATTERN1 + m_pattern;
		m_patternChange = false;
	}
}

void CBoss::CurStatusInStr(std::wstring & out)
{
	switch (m_status)
	{
	case STATUS_IDLE:
		out = L"Idle";
		break;

	case STATUS_PATTERN1:
		out = L"Pattern1";
		break;

	case STATUS_PATTERN2:
		out = L"Pattern2";
		break;

	case STATUS_JUMP:
		out = L"Jump";
		break;

	case STATUS_DIZZY:
		out = L"Dizzy";
		break;

	case STATUS_EXHAUSTED:
		out = L"Exhausted";
		break;
	}
}
