#ifndef UISHADER_H__
#define UISHADER_H__

#include "Shader.h"
BEGIN(Engine)
class ENGINE_DLL CUIShader final : public CShader
{
public:
	explicit						 CUIShader(void);
									~CUIShader(void);

public:
	static		CUIShader*			Create		(void);

				void				Awake		(void) override;
				void				Start		(void) override;

				void				PreRender	(CGraphicsC* pGC) override;
				void				Render		(CGraphicsC* pGC) override;
				void				PostRender	(CGraphicsC* pGC) override;

				void				OnDestroy	(void) override;

				void				OnEnable	(void) override;
				void				OnDisable	(void) override;

private:
				void				LoadShader	(void) override;
};
END
#endif // !UISHADER_H__
