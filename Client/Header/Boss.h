#ifndef BOSS_H
#define BOSS_H

#include "Object.h"

class CRollerBlade;
class CSandBag;
class CMafiaBall;
class CBoss final : public Engine::CObject
{
#define PAHSE_CHANGE_TIME_LIMIT 0.5f
	enum EAniIndex
	{
		ANI_IDLE	= 4,
		ANI_JUMP	= 15,
		ANI_DIZZY	= 17,
		ANI_SPIN	= 1,
		ANI_THROW	= 2,
		ANI_CHARGE  = 18,
		ANI_BRAVO	= 6,
		ANI_ANGRY0  = 0,
		ANI_DEAD	= 9
	};

	enum EStatus
	{
		STATUS_IDLE,
		STATUS_WALKING,
		STATUS_PATTERN1,
		STATUS_PATTERN2,
		STATUS_JUMP,
		STATUS_DIZZY,
		STATUS_EXHAUSTED
	};

	enum EPhase
	{
		PHASE_ZERO,
		PHASE_ONE,
		PHASE_TWO,
		PHASE_THREE
	};
	SMART_DELETER_REGISTER
private:
	explicit						CBoss				(void);
								   ~CBoss				(void);

public:
	static		SP(CBoss)			Create				(_bool isStatic);

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
				void				Jump				(_float3 goalPos, _float time, 
														 _bool phaseChange, _bool patternChange,
														 _float gravityConstant = 1.f);

				void				JumpDone			(void);

				void				Dizzy				(void);
				void				Exhausted			(void);
				void				PatternOne			(void);
				void				PatternTwo			(void);

				void				UpdateAnimation		(void);

				void				PhaseChange			(void);
				void				PatternChange		(void);

private:
				void				CurStatusInStr		(std::wstring& out);
private:
	static		_uint						m_s_uniqueID;

	std::vector<CRollerBlade*>				m_vRoller;
	std::vector<CRollerBlade*>				m_vChargeRoller;

	std::vector<CSandBag*>					m_vSandBags;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,			nullptr,		Collision)
	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,			nullptr,		RigidBody)		

	GETTOR		(Engine::CTransformC*,		m_pPlayerTransform,		nullptr,		PlayerTransform)
	GETTOR		(CRollerBlade*,				m_pLeftRoller,			nullptr,		LeftRoller)
	GETTOR		(CRollerBlade*,				m_pRightRoller,			nullptr,		RightRoller)
	GETTOR		(CMafiaBall*,				m_pMafiaBall,			nullptr,		MafiaBall)

	GETTOR_SETTOR	(_bool,					m_onGround,				false,			OnGround)
	GETTOR_SETTOR	(_bool,					m_phaseChange,			false,			PhaseChange)
	GETTOR_SETTOR	(_bool,					m_patternChange,		false,			PatternChange)
	GETTOR_SETTOR	(_bool,					m_gotHit,				false,			GotHit)
	GETTOR_SETTOR	(_bool,					m_fixedDir,				false,			FixedDir)
	GETTOR_SETTOR	(_bool,					m_initNow,				false,			InitNow)

	GETTOR_SETTOR	(_int,					m_phase,				PHASE_ZERO,		Phase)
	GETTOR_SETTOR	(_int,					m_pattern,				2,				Pattern)
	GETTOR_SETTOR	(_int,					m_status,				STATUS_IDLE,	Status)
	GETTOR_SETTOR	(_int,					m_lastStatus,			STATUS_IDLE,	LastStatus)
	GETTOR_SETTOR	(_int,					m_saveStatus,			UNDEFINED,		SaveStatus)

	GETTOR_SETTOR	(_float,				m_phaseChangeTimer,		0.f,			PhaseChangeTimer)
	GETTOR_SETTOR	(_float,				m_dizzyTimer,			0.f,			DizzyTimer)
	GETTOR_SETTOR	(_float,				m_dizzyDuration,		99.f,			DizzyDuration)
	GETTOR_SETTOR	(_float,				m_chargeTimer,			0.f,			ChargeTimer)
	GETTOR_SETTOR	(_float,				m_chargeDuration,		3.f,			ChargeDuration)
	GETTOR_SETTOR	(_float,				m_throwTimer,			0.f,			ThrowTimer)
	GETTOR_SETTOR	(_float,				m_sandBagTimer,			0.f,			SandBagTimer)
	GETTOR_SETTOR	(_float,				m_sandBagDuration,		3.3f,			SandBagDuration)
	GETTOR_SETTOR	(_float,				m_floatingTimer,		0.f,			FloatingTimer)
	GETTOR_SETTOR	(_float,				m_floatingDuration,		2.f,			FloatingDuration)
	GETTOR_SETTOR	(_float,				m_stompTimer,			0.f,			StompTimer)
	GETTOR_SETTOR	(_float,				m_stompDuration,		1.5f,			StompDuration)
	GETTOR_SETTOR	(_float,				m_exhaustedTimer,		0.f,			ExhaustedTimer)
	GETTOR_SETTOR	(_float,				m_exhaustedDuration,	2.f,			ExhaustedDuration)

	GETTOR_SETTOR	(_int,					m_aniIndex,				0,				AniIndex)

	GETTOR_SETTOR	(_int,					m_rollerInHand,			2,				RollerInHand)
	GETTOR_SETTOR	(_int,					m_rollerIndex,			0,				RollerIndex)
	GETTOR_SETTOR	(_int,					m_rollerCoef,			1,				RollerCoef)

	GETTOR_SETTOR	(_int,					m_curWave,				0,				CurWave)
	GETTOR_SETTOR	(_int,					m_sandBagWave,			5,				SandBagWave)
	GETTOR_SETTOR	(_int,					m_sandBagExceptLane,	0,				SandBagExceptLane)

	GETTOR_SETTOR	(_int,					m_exhaustedHitCount,	0,				ExHaustedHitCount)

	GETTOR_SETTOR	(_float3,				m_jumpGoalPos,			ZERO_VECTOR,	JumpGoalPos)
	GETTOR_SETTOR	(_float3,				m_shootDir,				ZERO_VECTOR,	ShootDir)
};

#endif