#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class CPlayer final : public Engine::CObject
{
	enum EAniIndex
	{
		ANI_IDLE		= 14,
		ANI_RUN			= 15,
		ANI_JUMP		= 9,
		ANI_DOUBLEJUMP	= 8,
		ANI_FALL		= 9,
		ANI_SLIDE		= 11,
		ANI_SLIDEDONE	= 10,
		ANI_ATTACK		= 6,
		ANI_ATTACK2		= 5,
		ANI_ATTACK3		= 4,
		ANI_ATTACK4		= 3,
		ANI_ATTACK5		= 2
	};

	enum EStatus
	{
		STATUS_IDLE			= 0,
		STATUS_WALK			= 1,
		STATUS_RUN			= 2,
		STATUS_JUMP			= 3,
		STATUS_DOUBLEJUMP	= 4,
		STATUS_FALL			= 5,
		STATUS_ATTACK		= 6,
		STATUS_SLIDE		= 7,
		STATUS_SLIDEDONE	= 8
	};

	SMART_DELETER_REGISTER
private:
	explicit						CPlayer				(void);
								   ~CPlayer				(void);

public:
	static		SP(CPlayer)			Create				(_bool isStatic);

				SP(Engine::CObject)	MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

				void				SetBasicName		(void) override;

public:
				void				OnCollisionEnter	(Engine::_CollisionInfo ci);
				void				OnCollisionStay		(Engine::_CollisionInfo ci);
				void				OnCollisionExit		(Engine::_CollisionInfo ci);

private:
				void				Move				(void);
				void				Attack				(void);
				void				Jump				(void);
				void				Fall				(void);
				void				Slide				(void);
				void				UpdateAnimation		(void);

private:
				void				CurStatusInStr		(std::wstring& pOut);

private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,			nullptr,		Collision)
	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,			nullptr,		RigidBody)

	GETTOR		(SP(Engine::CObject),		m_spSCObject,			nullptr,		SCObject)

	GETTOR_SETTOR	(_int,					m_lastStatus,			STATUS_IDLE,	LastStatus)
	GETTOR_SETTOR	(_int,					m_status,				STATUS_IDLE,	Status)

	GETTOR_SETTOR	(_int,					m_aniIndex,				0,				AniIndex)
	GETTOR_SETTOR	(_float,				m_aniPeriod,			0.f,			AniPeriod)

	GETTOR_SETTOR	(_float,				m_walkSpeed,			3,				WalkSpeed)
	GETTOR_SETTOR	(_float,				m_runSpeed,				9,				RunSpeed)
	GETTOR_SETTOR	(_float,				m_moveSpeed,			0,				MoveSpeed)
	GETTOR_SETTOR	(_float3,				m_moveDir,				ZERO_VECTOR,	MoveDir)

	GETTOR_SETTOR	(_float,				m_jumpAmount,			70,				JumpAmount)
	GETTOR_SETTOR	(_float,				m_doubleJumpAmount,		900,			DoubleJumpAmount)
	GETTOR_SETTOR	(_float,				m_jumpTimer,			0,				JumpTimer)
	GETTOR_SETTOR	(_float,				m_jumpLimit,			0.1f,			JumpLimit)
	GETTOR_SETTOR	(_int,					m_jumpChance,			1,				JumpChance)

	GETTOR_SETTOR	(_bool,					m_attackCombo,			false,			AttackTimerStart)
	GETTOR_SETTOR	(_float,				m_attackTimer,			0,				AttackTimer)

	GETTOR_SETTOR	(_float,				m_punchTimer,			0,				PunchTimer)
	GETTOR_SETTOR	(_float,				m_punchLimit,			0.2f,			PunchLimit)
	GETTOR_SETTOR	(_int,					m_punchCount,			0,				PunchCount)

	GETTOR_SETTOR	(_float,				m_slideAmount,			600,			SlideAmount)
	GETTOR_SETTOR	(_float,				m_slideSpeed,			9,				SlideSpeed)

	GETTOR_SETTOR	(_bool,					m_onGround,				false,			OnGround)
	GETTOR_SETTOR	(_bool,					m_controllable,			true,			ControlAble)
};

#endif