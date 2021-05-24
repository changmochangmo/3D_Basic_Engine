#ifndef PLAYERATTACK_H
#define PLAYERATTACK_H

#include "Object.h"

class CPlayerAttack final : public Engine::CObject
{
SMART_DELETER_REGISTER
private:
	explicit						CPlayerAttack		(void);
								   ~CPlayerAttack		(void);

public:
	static		SP(CPlayerAttack)	Create				(_bool isStatic);

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
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,		nullptr,		Collision)
	GETTOR_SETTOR	(Engine::CObject*,		m_pPlayer,			nullptr,		Player)

	GETTOR		(_bool,						m_lastFrameEnabled,	false,			LastFrameEnabled)
};

#endif