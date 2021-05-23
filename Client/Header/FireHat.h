#ifndef FIREHAT_H
#define FIREHAT_H

#include "Object.h"

class CFireHat final : public Engine::CObject
{
SMART_DELETER_REGISTER
private:
	explicit						CFireHat			(void);
								   ~CFireHat			(void);

public:
	static		SP(CFireHat)		Create				(_bool isStatic);

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


private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)

	GETTOR		(_mat*,						m_pParentBoneMatrix,	{},				ParentBoneMatrix)
	GETTOR		(const _mat*,				m_pParentWorldMatrix,	{},				ParentWorldMatrix)

	GETTOR_SETTOR	(Engine::CObject*,		m_pPlayer,				nullptr,		Player)
};

#endif