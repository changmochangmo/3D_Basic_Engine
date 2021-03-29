#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class CPlayer final : public Engine::CGameObject
{
	SMART_DELETER_REGISTER
protected:
	explicit				CPlayer			(void);
						   ~CPlayer			(void);

public:
	static			SHARED(CPlayer)					Create				(void);

					SHARED(Engine::CGameObject)		MakeClone			(void) override;
		
					void							Awake				(void) override;
					void							Start				(void) override;
		
					_uint							FixedUpdate			(void) override;
					_uint							Update				(void) override;
					_uint							LateUpdate			(void) override;
		
					void							OnDestroy			(void) override;
		
					void							OnEnable			(void) override;
					void							OnDisable			(void) override;

private:
					SHARED(Engine::CTransformComponent) m_spTransform;
					SHARED(Engine::CMeshComponent)		m_spMesh;
					SHARED(Engine::CTextureComponent)	m_spTexture;
					SHARED(Engine::CGraphicsComponent)	m_spGraphics;
};

#endif