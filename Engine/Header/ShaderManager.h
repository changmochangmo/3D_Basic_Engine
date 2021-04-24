#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CShader;
class ENGINE_DLL CShaderManager final : public CEngine
{
	DECLARE_SINGLETON(CShaderManager)
public:
			void		Awake		(void) override;
			void		Start		(void);
			void		OnDestroy	(void);
			void		OnEnable	(void);
			void		OnDisable	(void);

			CShader*	GetShader	(_int shaderKey);

private:
			HRESULT		AddShader	(CShader* pShader);

private:
	std::unordered_map<_int, CShader*> m_mShaders;
};
END

#endif