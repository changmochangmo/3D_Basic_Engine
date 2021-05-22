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
																  
					void				FixedUpdate			(void);
					void				Update				(void);
					void				LateUpdate			(void);
					
					void				OnDestroy			(void);

					void				OnEnable			(void);
					void				OnDisable			(void);

					void				SceneChange			(CScene* pScene,
															 _bool alreadyStarted = false,
															 _bool deleteThis = true);


private:
					void				OrganizeScene		(_bool deleteCurScene);


private:
	std::stack<CScene*>	m_sScene;

	GETTOR			(_bool,		m_sceneChanged,		false,			SceneChanged)
	GETTOR_SETTOR	(CScene*,	m_pPrevScene,		nullptr,		PrevScene)
	GETTOR_SETTOR	(CScene*,	m_pCurScene,		nullptr,		CurScene)
};
END

#endif
