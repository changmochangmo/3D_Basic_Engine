#ifndef BOSS_H
#define BOSS_H

#include "Object.h"

class CBoss final : public Engine::CObject
{
	enum EAniIndex
	{
		ANI_IDLE = 4,
		ANI_JUMP = 15
	};

	enum EStatus
	{
		//여기부터
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

				void				Jump				(_float3 goalPos, _float time);


private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,			nullptr,		Collision)
	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,			nullptr,		RigidBody)		

	GETTOR_SETTOR	(_bool,					m_onGround,				false,			OnGround)

	GETTOR_SETTOR	(_int,					m_phase,				0,				Phase)
};

#endif