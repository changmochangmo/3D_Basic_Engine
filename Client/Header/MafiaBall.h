#ifndef MAFIABALL_H
#define MAFIABALL_H

#include "Object.h"

class CMafiaBall final : public Engine::CObject	
{
	SMART_DELETER_REGISTER
private:
	explicit						CMafiaBall			(void);
								   ~CMafiaBall			(void);

public:
	static		SP(CMafiaBall)		Create				(_bool isStatic);

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

	GETTOR_SETTOR(CObject*,					m_pBoss,				nullptr,		Boss)

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,			nullptr,		Collision)
	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,			nullptr,		RigidBody)

	//GETTOR_SETTOR	(_float3,				m_minHoleLine,			
	
};

#endif