#ifndef SANDBAG_H
#define SANDBAG_H

#include "Object.h"

class CSandBag final : public Engine::CObject	
{
	SMART_DELETER_REGISTER
private:
	explicit						CSandBag			(void);
								   ~CSandBag			(void);

public:
	static		SP(CSandBag)		Create				(_bool isStatic);

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

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,			nullptr,		Collision)
	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,			nullptr,		RigidBody)
	
	GETTOR_SETTOR	(_int,					m_laneNumber,			UNDEFINED,		LaneNumber)

	GETTOR_SETTOR	(_float,				m_fallingTimer,			0.f,			FallingTimer)
	GETTOR_SETTOR	(_float,				m_fallingDuration,		2.f,			FallingDuration)

	GETTOR_SETTOR	(_float3,				m_startPos,				ZERO_VECTOR,	StartPos)
	GETTOR_SETTOR	(_float,				m_interval,				0.f,			Interval)

	GETTOR_SETTOR	(_float,				m_readyPosY,			6.f,			ReadyPosY)

	GETTOR_SETTOR	(_bool,					m_ready,				false,			Ready)
	
};

#endif