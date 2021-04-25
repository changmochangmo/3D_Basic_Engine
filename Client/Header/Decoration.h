#ifndef DECORATION_H
#define DECORATION_H

#include "Object.h"

class CDecoration abstract : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CDecoration			(void);
								   ~CDecoration			(void);

public:
				SP(Engine::CObject)	MakeClone			(void) PURE;
		
	virtual		void				Awake				(void) PURE;
	virtual		void				Start				(void) PURE;

	virtual		void				FixedUpdate			(void) PURE;
	virtual		void				Update				(void) PURE;
	virtual		void				LateUpdate			(void) PURE;

	virtual		void				OnDestroy			(void) PURE;

	virtual		void				OnEnable			(void) PURE;
	virtual		void				OnDisable			(void) PURE;

private:
	GETTOR		(SP(Engine::CMeshC),		m_spMesh,			nullptr,	Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,		nullptr,	Graphics)
};

#endif