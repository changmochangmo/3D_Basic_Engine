#ifndef COLORSHADER_H
#define COLORSHDAER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CDebugShader final : public CShader
{
private:
	explicit			CDebugShader					(void);
					   ~CDebugShader					(void);

public:
	static		CDebugShader*		Create				(void);

				void				Awake				(void) override;
				void				Start				(void) override;

				void				PreRender			(CGraphicsC* pGC) override;
				void				Render				(CGraphicsC* pGC) override;
				void				PostRender			(CGraphicsC* pGC) override;

				void				OnDestroy			(void) override;

				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

private:
				void				LoadShader			(void) override;
};

END
#endif

