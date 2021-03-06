#ifndef SHADER_H
#define SHADER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CShader abstract : public CEngine
{
public:	
	explicit			CShader				(void);
	virtual			   ~CShader				(void);

public:
	virtual		void	Awake				(void) PURE;
	virtual		void	Start				(void) PURE;

	virtual		void	PreRender			(CGraphicsC* pGC) PURE;
	virtual		void	Render				(CGraphicsC* pGC) PURE;
	virtual		void	PostRender			(CGraphicsC* pGC) PURE;

	virtual		void	OnDestroy			(void) PURE;

	virtual		void	OnEnable			(void) PURE;
	virtual		void	OnDisable			(void) PURE;

	
protected:
	virtual		void	LoadShader			(void) PURE;

protected:
	GETTOR		(std::wstring,		m_filePath,		L"",			FilePath)
	GETTOR		(LPD3DXEFFECT,		m_pShader,		nullptr,		Shader)
	GETTOR		(_int,				m_shaderType,	UNDEFINED,		ShaderType)
};
END
#endif // !SHADER_H