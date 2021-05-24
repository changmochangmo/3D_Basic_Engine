#ifndef MAFIA_H
#define MAFIA_H

#include "Object.h"

class CMafia final	: public Engine::CObject
{
	enum EAniIndex
	{
		ANI_IDLE	= 0,
		ANI_ATTACK	= 7,
		ANI_HURT	= 6,
		ANI_MOVE	= 6
	};

	enum EStatus
	{
		STATUS_IDLE,
		STATUS_MOVE,
		STATUS_ATTACK,
		STATUS_HURT,
		STATUS_DYING
	};
	SMART_DELETER_REGISTER
private:
	explicit						CMafia				(void);
								   ~CMafia				(void);

public:
	static		SP(CMafia)			Create				(_bool isStatic);

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

public:
				void				UpdateAnimation		(void);

private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,			nullptr,		Collision)
	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,			nullptr,		RigidBody)	
	GETTOR		(SP(Engine::CFadeInOutC),	m_spFadeInOut,			nullptr,		FadeInOut)	

	GETTOR		(Engine::CTransformC*,		m_pPlayerTransform,		nullptr,		PlayerTransform)

	GETTOR		(_bool,						m_onGround,				false,			OnGround)
	GETTOR_SETTOR	(_bool,					m_isHurt,				false,			IsHurt)
	GETTOR_SETTOR	(_bool,					m_fightAble,			false,			FightAble)

	GETTOR_SETTOR	(_int,					m_status,				STATUS_IDLE,	Status)
	GETTOR_SETTOR	(_int,					m_lastStatus,			STATUS_IDLE,	LastStatus)
	GETTOR_SETTOR	(_int,					m_aniIndex,				ANI_IDLE,		AniIndex)
	GETTOR_SETTOR	(_int,					m_hp,					6,				HP)

	GETTOR_SETTOR	(_float,				m_hurtTimer,			0.5f,			HurtTimer)
	GETTOR_SETTOR	(_float,				m_redTimer,				0.0f,			RedTimer)
};


#endif