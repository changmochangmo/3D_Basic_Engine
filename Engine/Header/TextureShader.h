#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CTextureShader final : public CShader
{
private:
	explicit			CTextureShader					(void);
					   ~CTextureShader					(void);

public:
	static		CTextureShader*		Create				(void);

				void				Awake				(void) override;
				void				Start				(void) override;

				void				PreRender			(CGraphicsC* pGraphics) override;
				void				Render				(CGraphicsC* pGraphics) override;
				void				PostRender			(CGraphicsC* pGraphics) override;

				void				OnDestroy			(void) override;

				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

private:
				void				LoadShader			(void) override;
				void				RenderStaticMesh	(CGraphicsC* pGC, _int index);
				void				RenderDynamicMesh	(CGraphicsC* pGC, _int index);
};
END
#endif