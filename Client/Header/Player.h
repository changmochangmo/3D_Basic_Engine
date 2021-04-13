#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class CPlayer final : public Engine::CGameObject
{
	SMART_DELETER_REGISTER
private:
	explicit								CPlayer			(void);
										   ~CPlayer			(void);

public:
	static		SP(CPlayer)					Create			(_bool isStatic);

				SP(Engine::CGameObject)		MakeClone		(void) override;
		
				void						Awake			(void) override;
				void						Start			(void) override;
		
				void						FixedUpdate		(void) override;
				void						Update			(void) override;
				void						LateUpdate		(void) override;
		
				void						OnDestroy		(void) override;
		
				void						OnEnable		(void) override;
				void						OnDisable		(void) override;

public:
				void						SetBasicName	(void) override;

private:
	static		_uint						m_s_uniqueID;

				SP(Engine::CTransformC)		m_spTransform;
				SP(Engine::CMeshC)			m_spMesh;
				SP(Engine::CTextureC)		m_spTexture;
				SP(Engine::CGraphicsC)		m_spGraphics;
};

#endif