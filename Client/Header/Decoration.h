#ifndef DECORATION_H
#define DECORATION_H

#include "Object.h"

class CDecoration : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CDecoration			(void);
								   ~CDecoration			(void);

public:
	static		SP(CDecoration)		Create				(_bool isStatic);
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

				void				AddAnimationIndex	(_int index);
private:
	static		_uint						m_s_uniqueID;

	std::vector<_int> m_vAnimationIndices;
	GETTOR		(_int,						m_aniIndex,			0,			AniIndex)
	GETTOR		(SP(Engine::CMeshC),		m_spMesh,			nullptr,	Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,		nullptr,	Graphics)
};

#endif