#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

class CCamera final : public Engine::CObject
{
	SMART_DELETER_REGISTER

private:
	explicit								CCamera				(void);
										   ~CCamera				(void);

public:
	static		SP(CCamera)					Create				(void);
				SP(Engine::CObject)			MakeClone			(void) override;
		
				void						Awake				(void) override;
				void						Start				(void) override;
		
				void						FixedUpdate			(void) override;
				void						Update				(void) override;
				void						LateUpdate			(void) override;
		
				void						OnDestroy			(void) override;
		
				void						OnEnable			(void) override;
				void						OnDisable			(void) override;

				void						SetBasicName		(void) override;

public:
				void						OnCollisionEnter	(Engine::_CollisionInfo ci);
				void						OnCollisionStay		(Engine::_CollisionInfo ci);
				void						OnCollisionExit		(Engine::_CollisionInfo ci);
				

public:

private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CCameraC),		m_spCamera,			nullptr,	Camera)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,		nullptr,	Collision)
	GETTOR		(SP(Engine::CDebugC),		m_spDebug,			nullptr,	Debug)

	GETTOR		(Engine::CRayCollider*,		m_pCamRayCollider,	nullptr,	CamRayCollider)
};

#endif