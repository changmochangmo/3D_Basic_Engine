#ifndef TERRAIN_H
#define TERRAIN_H

#include "Object.h"

class CTerrain final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CTerrain			(void);
								   ~CTerrain			(void);

public:
	static		SP(CTerrain)		Create				(_bool isStatic);

				SP(Engine::CObject)	MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

public:
				void				SetBasicName		(void) override;

private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,			nullptr,	Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,		nullptr,	Graphics)
};

#endif