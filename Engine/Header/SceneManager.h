#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Engine.h"
#include "Scene.h"

BEGIN(Engine)
class ENGINE_DLL CSceneManager final : public CEngine
{
	DECLARE_SINGLETON(CSceneManager)
public:

					void				Awake				(void) override;
					void				Start				(void);
																  
					_uint				FixedUpdate			(void);
					_uint				Update				(void);
					_uint				LateUpdate			(void);
					
					void				OnDestroy			(void);

					void				OnEnable			(void);
					void				OnDisable			(void);

					void				SceneChange			(SHARED(CScene) pScene, 
															bool needToBeCleaned = true);


private:
					void				OrganizeScene		(void);


private:
	std::stack<SHARED(CScene)>			m_sScene;

	GETTOR_SETTOR	(bool,				m_needToBeCleaned,	false,			NeedToBeCleaned)
	GETTOR_SETTOR	(SHARED(CScene),	m_pPrevScene,		nullptr,		PrevScene)
	GETTOR_SETTOR	(SHARED(CScene),	m_pCurScene,		nullptr,		CurScene)
	GETTOR_SETTOR	(SHARED(CScene),	m_pNextScene,		nullptr,		NextScene)
	GETTOR_SETTOR	(SHARED(CScene),	m_pStaticScene,		nullptr,		StaticScene)
	GETTOR_SETTOR	(std::wstring  ,	m_ws_SceneName,     L"",            SceneName)

	GETTOR(std::vector<UNITINFO>, m_vUnitInfo, {}, UnitInfo)
};
END

#endif
