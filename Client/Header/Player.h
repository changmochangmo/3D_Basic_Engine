#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class CPlayer final : public Engine::CObject
{
	enum EAniIndex
	{
		ANI_IDLE	= 14,
		ANI_RUN		= 15
	};

	enum EStatus
	{
		Idle		= 0,
		Walk		= 1,
		Run			= 2,
		Jump		= 3,
		Fall		= 4
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
				void				UpdateAnimation		(void);
				void				Movement			(void);
				void				JumpAndFall			(void);

private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,		nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,	nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,	nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,	nullptr,		Collision)

	GETTOR		(EStatus,					m_lastStatus,	Idle,			LastStatus)
	GETTOR		(EStatus,					m_status,		Idle,			Status)

	GETTOR_SETTOR	(_float,				m_walkSpeed,	3,				WalkSpeed)
	GETTOR_SETTOR	(_float,				m_runSpeed,		9,				RunSpeed)
	GETTOR_SETTOR	(_float3,				m_moveDir,		ZERO_VECTOR,	MoveDir)

	GETTOR_SETTOR	(_bool,					m_onGround,		false,			OnGround)
	GETTOR_SETTOR	(_int,					m_jumpChance,	2,				JumpChance)
};

#endif