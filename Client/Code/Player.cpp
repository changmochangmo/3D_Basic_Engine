#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "FRC.h"
#include "DynamicMesh.h"
#include "MeshData.h"
#include "CameraManager.h"
#include "TextManager.h"
#include "ObjectFactory.h"
#include "UserInterface.h"
#include "SceneManager.h"
#include "JumpHat.h"
#include "FireHat.h"
#include "BossScene.h"
#include "CameraManager.h"
#include "PlayerAttack.h"

_uint CPlayer::m_s_uniqueID = 0;

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	OnDestroy();
}

SP(CPlayer) CPlayer::Create(_bool isStatic)
{
	SP(CPlayer) spInstance(new CPlayer, Engine::SmartDeleter<CPlayer>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPlayer::MakeClone(void)
{
	SP(CPlayer) spClone(new CPlayer, Engine::SmartDeleter<CPlayer>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();
	return spClone;
}

//현재 프로토타입만 어웨이크를 타고, 클론은 어웨이크가 된 프로토타입을 복사해감.
void CPlayer::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Player;
	m_dataID	= (_int)EDataID::Player;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();

	m_spTransform->SetSize(_float3(0.01f, 0.01f, 0.01f));
}

void CPlayer::Start(void)
{
	__super::Start();
	m_spCollision->SetOffsetBS(_float3(0, 0.5f, 0));
	m_spCollision->SetRadiusBS(1.1f);
	m_spTransform->AddPositionY(0.2f);

	m_spSCObject = Engine::ADD_CLONE(L"EmptyObject", Engine::GET_CUR_SCENE, true, L"PlayerSC", (_int)ELayerID::Player);
	m_spSCObject->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CSphereCollider::Create(0.325f, _float3(0, 0.35f, 0)));
	m_spSCObject->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Player);

	m_spJumpHat =
		std::dynamic_pointer_cast<CJumpHat>(Engine::ADD_CLONE(L"JumpHat", Engine::GET_CUR_SCENE, false));
	m_spJumpHat->SetIsEnabled(false);
	m_spJumpHat->SetPlayer(this);

	m_spFireHat =
		std::dynamic_pointer_cast<CFireHat>(Engine::ADD_CLONE(L"FireHat", Engine::GET_CUR_SCENE, false));
	m_spFireHat->SetIsEnabled(false);
	m_spFireHat->SetPlayer(this);


	m_spPlayerAttack = 
		std::dynamic_pointer_cast<CPlayerAttack>(Engine::ADD_CLONE(L"PlayerAttack", Engine::GET_CUR_SCENE, false));
	m_spPlayerAttack->SetIsEnabled(false);

	m_spLifeUI = 
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"PlayerLife", Engine::GET_CUR_SCENE, false, L"", (_int)ELayerID::UI));

	m_spJumpHatUI =
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"JumpHatUI", Engine::GET_CUR_SCENE, false, L"", (_int)ELayerID::UI));
	m_spJumpHatUI->SetIsEnabled(false);
	m_spFireHatUI = 
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"FireHatUI", Engine::GET_CUR_SCENE, false, L"", (_int)ELayerID::UI));
	m_spFireHatUI->SetIsEnabled(false);

	m_spSCObject->AddComponent<Engine::CDebugC>();
	m_curCamMode = Engine::ECameraMode::Follower;
	m_spTexture->SetColor(D3DXCOLOR(1, 0, 0, 1));
	//m_spRigidBody->SetUseGravity(false);
}

void CPlayer::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CPlayer::Update(void)
{
	__super::Update();
	m_spSCObject->GetTransform()->SetPosition(m_spTransform->GetPosition());
	m_spLifeUI->GetTexture()->SetTexIndex(m_life);

	Engine::REWRITE_TEXT(L"Test0", std::to_wstring(m_spTransform->GetPosition().x) + L", \n" + 
								   std::to_wstring(m_spTransform->GetPosition().y) + L", \n" +
								   std::to_wstring(m_spTransform->GetPosition().z));
}

void CPlayer::LateUpdate(void)
{
	m_status = STATUS_IDLE;
	if (m_controllable)
	{
		Move();
		Attack();
		Jump();
		Slide();
	}
	else
	{
		m_punchTimer += GET_DT;
		if (m_punchTimer >= m_punchLimit)
		{
			m_punchTimer = 0.f;
			m_controllable = true;
		}
	}
	Fall();
	Hurt();
	SwapHat();
	Skill();
	UpdateAnimation();

	//std::wstring curState;
	//CurStatusInStr(curState);
	//Engine::REWRITE_TEXT(L"Test1", curState);
	

		

	m_lastStatus = m_status;
	m_onGround = false;
	__super::LateUpdate();
}

void CPlayer::OnDestroy(void)
{
	__super::OnDestroy();
}

void CPlayer::OnEnable(void)
{
	__super::OnEnable();
}

void CPlayer::OnDisable(void)
{
	__super::OnDisable();
}

void CPlayer::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}


void CPlayer::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (ci.normal.y - EPSILON <= -0.7f)
	{
		m_status = STATUS_IDLE;
		m_onGround = true;
		m_spRigidBody->SetVelocity(ZERO_VECTOR);
	}
	else if (ci.normal.y + EPSILON >= 0.7)
	{
		m_jumpTimer = m_jumpLimit;
		m_spRigidBody->SetVelocity(ZERO_VECTOR);
	}
}

void CPlayer::OnCollisionStay(Engine::_CollisionInfo ci)
{
	if (ci.normal.y - EPSILON <= -0.7)
	{
		m_status = STATUS_IDLE;
		m_onGround = true;
	}
	else if (ci.normal.y + EPSILON >= 0.7)
	{
		m_jumpTimer = m_jumpLimit;
	}
}

void CPlayer::OnCollisionExit(Engine::_CollisionInfo ci)
{
}


void CPlayer::Move(void)
{
	SP(Engine::CTransformC) mainCamTransform = Engine::GET_MAIN_CAM->GetOwner()->GetTransform();

	m_moveDir = ZERO_VECTOR;
	_int saveStatus = UNDEFINED;
	if (Engine::GET_MAIN_CAM->GetMode() == Engine::ECameraMode::Follower ||
		Engine::GET_MAIN_CAM->GetMode() == Engine::ECameraMode::Edit)
	{
		if (Engine::IMKEY_PRESS(KEY_W))
		{
			_float3 dir = m_spTransform->GetPosition() - mainCamTransform->GetPosition();
			dir.y = 0;
			D3DXVec3Normalize(&dir, &dir);
			m_moveDir += dir;
		}
		if (Engine::IMKEY_PRESS(KEY_A))
		{
			_float3 dir = m_spTransform->GetPosition() - mainCamTransform->GetPosition();
			dir.y = 0;
			D3DXVec3Normalize(&dir, &dir);
			D3DXVec3Cross(&dir, &dir, &UP_VECTOR);

			m_moveDir += dir;
		}
		if (Engine::IMKEY_PRESS(KEY_S))
		{
			_float3 dir = mainCamTransform->GetPosition() - m_spTransform->GetPosition();
			dir.y = 0;
			D3DXVec3Normalize(&dir, &dir);

			m_moveDir += dir;
		}
		if (Engine::IMKEY_PRESS(KEY_D))
		{
			_float3 dir = m_spTransform->GetPosition() - mainCamTransform->GetPosition();
			dir.y = 0;
			D3DXVec3Normalize(&dir, &dir);
			D3DXVec3Cross(&dir, &UP_VECTOR, &dir);

			m_moveDir += dir;
		}

		D3DXVec3Normalize(&m_moveDir, &m_moveDir);

		saveStatus = m_status;
		if (D3DXVec3LengthSq(&m_moveDir) > EPSILON)
		{
			m_spTransform->SetGoalForward(m_moveDir);
			m_spTransform->SetSlerpOn(true);
			m_status = STATUS_WALK;
			m_moveSpeed = m_walkSpeed;
			if (Engine::IMKEY_PRESS(KEY_SHIFT))
			{
				m_status = STATUS_RUN;
				m_moveSpeed = m_runSpeed;
			}

			m_spRigidBody->SetVelocityX(0.f);
			m_spRigidBody->SetVelocityZ(0.f);

			m_spTransform->AddPosition(m_moveDir * m_moveSpeed * GET_DT);
		}
		else
			m_moveSpeed = 0.f;
	}
	else if (Engine::GET_MAIN_CAM->GetMode() == Engine::ECameraMode::Movie ||
			 Engine::GET_MAIN_CAM->GetMode() == Engine::ECameraMode::Fixed)
	{
		if (Engine::IMKEY_PRESS(KEY_A))
		{
			m_moveDir += _float3(-1, 0, 0);
		}
		if (Engine::IMKEY_PRESS(KEY_D))
		{
			m_moveDir += _float3(1, 0, 0);
		}

		D3DXVec3Normalize(&m_moveDir, &m_moveDir);

		saveStatus = m_status;
		if (D3DXVec3LengthSq(&m_moveDir) > EPSILON)
		{
			m_spTransform->SetForward(m_moveDir);
			m_status = STATUS_WALK;
			m_moveSpeed = m_walkSpeed;
			if (Engine::IMKEY_PRESS(KEY_SHIFT))
			{
				m_status = STATUS_RUN;
				m_moveSpeed = m_runSpeed;
			}
			m_spRigidBody->SetVelocityX(0.f);
			m_spRigidBody->SetVelocityZ(0.f);

			m_spTransform->AddPosition(m_moveDir * m_moveSpeed * GET_DT);
		}
		else
			m_moveSpeed = 0.f;
	}
	

	if (m_onGround == false)
		m_status = saveStatus;
}

void CPlayer::Attack(void)
{
	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();
	Engine::CDynamicMesh* pFirstDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[0]);


	//Normal attack
	if (m_onGround && Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		if (m_lastStatus == STATUS_ATTACK && m_attackCombo == false)
			m_attackCombo = true;

		m_status = STATUS_ATTACK;
		//m_spTransform->AddPosition(m_spTransform->GetForward() * 15 * GET_DT);
		m_spPlayerAttack->SetIsEnabled(true);
		m_spPlayerAttack->GetTransform()->SetPosition(m_spTransform->GetPosition());
	}


	if (m_lastStatus == STATUS_ATTACK)
	{
		m_status = STATUS_ATTACK;

		if (pFirstDM->GetAniCtrl()->IsItEnd())
		{
			if (m_attackCombo)
			{
				if (m_punchCount >= 4)
				{
					m_punchCount = 0;
					m_status = STATUS_IDLE;
					m_controllable = false;
				}
				else
					++m_punchCount;

				m_attackCombo = false;
			}
			else
			{
				m_punchCount = 0;
				m_status = STATUS_IDLE;
				m_controllable = false;
			}
		}
	}


	if(m_status == STATUS_ATTACK)
		m_spTransform->AddPosition(-m_moveDir * m_moveSpeed * GET_DT);

}

void CPlayer::Jump(void)
{
	if (Engine::IMKEY_PRESS(KEY_SPACE) && m_jumpTimer < m_jumpLimit && m_spRigidBody->GetVelocity().y >= 0.f)
	{
		m_spRigidBody->AddForceY(m_jumpAmount);

		m_jumpTimer += GET_DT;
		m_status = STATUS_JUMP;
	}


	if (m_onGround == false && m_jumpChance > 0 && Engine::IMKEY_DOWN(KEY_SPACE))
	{
		m_jumpTimer = m_jumpLimit;
		m_spRigidBody->SetVelocityY(0);
		m_spRigidBody->AddForceY(m_doubleJumpAmount);
		m_jumpChance = 0;

		m_status = STATUS_DOUBLEJUMP;
	}
}

void CPlayer::Fall(void)
{
	if (m_status != STATUS_JUMP && m_status != STATUS_SLIDE)
	{
		if (m_onGround)
		{
			m_spRigidBody->AddForce(-GRAVITY * m_spRigidBody->GetGravityConstant());
			m_jumpTimer = 0.f;
			m_jumpChance = 1;
		}
		else
		{
			if (m_spRigidBody->GetVelocity().y <= 0 && m_status != STATUS_DOUBLEJUMP)
				m_status = STATUS_FALL;
			else
			{
				if (m_jumpChance == 1)
					m_status = STATUS_JUMP;
				else
					m_status = STATUS_DOUBLEJUMP;
			}
		}
	}
}

void CPlayer::Slide(void)
{
	if (m_lastStatus == STATUS_SLIDE)
	{
		if (m_onGround == false)
		{
			m_status = STATUS_SLIDE;
			m_spTransform->AddPosition(m_spTransform->GetForward() * m_slideSpeed * GET_DT);
		}
		else
		{
			m_status = STATUS_SLIDEDONE;
		}
	}
	if (Engine::IMKEY_DOWN(KEY_CONTROL) && m_status != STATUS_SLIDE)
	{
		m_jumpChance = 0;
		m_spRigidBody->SetVelocityY(0);
		m_spRigidBody->AddForceY(m_slideAmount);
		m_status = STATUS_SLIDE;
	}

	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();
	Engine::CDynamicMesh* pFirstDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[0]);

	if (m_lastStatus == STATUS_SLIDEDONE && m_status != STATUS_JUMP)
	{
		m_status = STATUS_SLIDEDONE;
	}
	if (m_status == STATUS_SLIDE || m_status == STATUS_SLIDEDONE)
		m_spTransform->AddPosition(-m_moveDir * m_moveSpeed * GET_DT);
}

void CPlayer::Hurt(void)
{
	_float deltaTime = GET_DT;
	if (m_isHurt)
	{
		if (m_hurtTimer == 0.f)
		{
			m_life--;

			_float3 hurtDir = -m_spTransform->GetForward();
			m_spRigidBody->AddForce(-m_spTransform->GetForward() * 200);
			m_spRigidBody->AddForce(UP_VECTOR * 200);
		}
		else if(m_hurtTimer > m_hurtDuration)
		{ 
			m_isHurt = false;
			m_hurtTimer = 0.f;
			m_spTexture->SetColor(D3DXCOLOR(1, 1, 1, 1));
			m_spGraphics->m_mtrl.Diffuse.b = 1;
			m_spGraphics->m_mtrl.Diffuse.g = 1;
			return;
		}
		if (m_alphaTimer <= 0.f)
		{
			if (m_spTexture->GetColor().a > 0.6f)
			{
				m_spTexture->SetColor(D3DXCOLOR(1, 1, 1, 0.5));
				m_spGraphics->m_mtrl.Diffuse.b = 0;
				m_spGraphics->m_mtrl.Diffuse.g = 0;
			}
			else
			{
				m_spTexture->SetColor(D3DXCOLOR(1, 1, 1, 1));
				m_spGraphics->m_mtrl.Diffuse.b = 1;
				m_spGraphics->m_mtrl.Diffuse.g = 1;
			}

			m_alphaTimer = 0.25f;
		}
		m_alphaTimer	-= deltaTime;
		m_hurtTimer		+= deltaTime;
	}
}

void CPlayer::SwapHat(void)
{
	if (Engine::IMKEY_PRESS(MOUSE_RIGHT))
	{
		m_spJumpHatUI->GetTransform()->SetPosition(225, 0, 0);
		m_spFireHatUI->GetTransform()->SetPosition(-225, 0, 0);

		static_cast<CBossScene*>(Engine::GET_CUR_SCENE)->GetMouseUI()->SetIsEnabled(true);
		Engine::GET_MAIN_CAM->SetMode(Engine::ECameraMode::Edit);
		m_spJumpHatUI->SetIsEnabled(true);
		m_spFireHatUI->SetIsEnabled(true);
		if (Engine::CInputManager::GetInstance()->GetMousePos().x > 0)
		{
			m_spJumpHatUI->GetTransform()->SetSize(130, 130, 0);
			m_spFireHatUI->GetTransform()->SetSize(100.f, 100.f, 0.f);

			m_spJumpHat->SetIsEnabled(true);
			m_spFireHat->SetIsEnabled(false);
		}
		else if (Engine::CInputManager::GetInstance()->GetMousePos().x < 0)
		{
			m_spJumpHatUI->GetTransform()->SetSize(100.f, 100.f, 0.f);
			m_spFireHatUI->GetTransform()->SetSize(130, 130, 0);
			m_spJumpHat->SetIsEnabled(false);
			m_spFireHat->SetIsEnabled(true);
		}
		else
		{
			m_spJumpHatUI->GetTransform()->SetSize(100.f, 100.f, 0.f);
			m_spFireHatUI->GetTransform()->SetSize(100, 100, 0);
			m_spJumpHat->SetIsEnabled(false);
			m_spFireHat->SetIsEnabled(false);
		}
		Engine::CFRC::GetInstance()->SetDtCoef(0.5f);
	}
	else if (Engine::IMKEY_UP(MOUSE_RIGHT))
	{
		static_cast<CBossScene*>(Engine::GET_CUR_SCENE)->GetMouseUI()->SetIsEnabled(false);
		Engine::CInputManager::GetInstance()->MoveMouseToCenter();
		Engine::GET_MAIN_CAM->SetMode(m_curCamMode);

		if (m_spJumpHat->GetIsEnabled())
		{
			m_spJumpHatUI->SetIsEnabled(true);
			m_spFireHatUI->SetIsEnabled(false);
		}
		else if(m_spFireHat->GetIsEnabled())
		{
			m_spJumpHatUI->SetIsEnabled(false);
			m_spFireHatUI->SetIsEnabled(true);
		}
		else
		{
			m_spJumpHatUI->SetIsEnabled(false);
			m_spFireHatUI->SetIsEnabled(false);
		}
		m_spJumpHatUI->GetTransform()->SetSize(50, 50, 0);
		m_spFireHatUI->GetTransform()->SetSize(50.f, 50.f, 0.f);
		m_spJumpHatUI->GetTransform()->SetPosition(0, -250, 0);
		m_spFireHatUI->GetTransform()->SetPosition(0, -250, 0);

		Engine::CFRC::GetInstance()->SetDtCoef(1.f);
	}
}

void CPlayer::Skill(void)
{
	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		if (m_spJumpHat->GetIsEnabled())
		{
			m_spRigidBody->AddForceY(m_jumpAmount * 20);
		}
		else if (m_spFireHat->GetIsEnabled())
		{

		}
	}
}


void CPlayer::UpdateAnimation(void)
{
	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();
	Engine::CDynamicMesh* pFirstDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[0]);
	if (m_lastStatus != m_status || pFirstDM->IsAnimationEnd())
	{
		_float	aniSpeed		= 1.f;
		_bool	fixTillEnd		= false;
		_double smoothTime		= 0.45;
		_float	changeWeight	= 0.9f;
		_bool	replay			= true;
		switch (m_status)
		{
		case STATUS_IDLE:
			m_aniIndex	= ANI_IDLE;
			smoothTime	= 0.2;
			break;

		case STATUS_WALK:
			m_aniIndex	= ANI_RUN;
			aniSpeed	= 2.f;
			break;

		case STATUS_RUN:
			m_aniIndex	= ANI_RUN;
			aniSpeed	= 3.f;
			break;

		case STATUS_JUMP:
			m_aniIndex	= ANI_JUMP;
			break;

		case STATUS_DOUBLEJUMP:
			m_aniIndex	= ANI_DOUBLEJUMP;
			aniSpeed	= 2.f;
			break;

		case STATUS_FALL:
			m_aniIndex = ANI_FALL;
			smoothTime = 0.2;
			break;

		case STATUS_ATTACK:
			m_aniIndex = ANI_ATTACK - m_punchCount;
			fixTillEnd		= true;
			aniSpeed		= 1.f;
			smoothTime		= 0.1;
			changeWeight	= 1.0;
			break;

		case STATUS_SLIDE:
			m_aniIndex		= ANI_SLIDE;
			break;

		case STATUS_SLIDEDONE:
			m_aniIndex		= ANI_SLIDEDONE;
			replay			= false;
		}
		for (_int i = 0; i < (_int)vMeshData.size(); ++i)
		{
			Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[i]);
			pDM->ChangeAniSet(m_aniIndex, fixTillEnd, smoothTime, changeWeight);
			pDM->GetAniCtrl()->SetSpeed(aniSpeed);
			pDM->GetAniCtrl()->SetReplay(replay);
		}
	}
}

void CPlayer::CurStatusInStr(std::wstring & pOut)
{
	switch (m_status)
	{
	case STATUS_IDLE:
		pOut = L"Idle";
		break;

	case STATUS_WALK:
		pOut = L"Walk";
		break;

	case STATUS_RUN:
		pOut = L"Run";
		break;

	case STATUS_JUMP:
		pOut = L"Jump";
		break;

	case STATUS_DOUBLEJUMP:
		pOut = L"DoubleJump";
		break;

	case STATUS_FALL:
		pOut = L"Fall";
		break;

	case STATUS_ATTACK:
		pOut = L"Attack";
		break;

	case STATUS_SLIDE:
		pOut = L"Slide";
		break;

	case STATUS_SLIDEDONE:
		pOut = L"SlideDone";
		break;
	}
}
