#ifndef WALL_H
#define WALL_H

#include "Object.h"

class CWall final : public Engine::CObject	
{
	SMART_DELETER_REGISTER
private:
	explicit						CWall				(void);
								   ~CWall				(void);

public:
	static		SP(CWall)			Create				(_bool isStatic);

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

	//GETTOR_SETTOR	(_float3,				m_minHoleLine,			
	
};

#endif