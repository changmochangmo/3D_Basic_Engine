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

					void				SceneChange			(CScene* pScene, 
															 _bool deleteThis = true);


private:
					void				OrganizeScene		(_bool deleteCurScene);


private:
	std::stack<CScene*>	m_sScene;

	GETTOR_SETTOR	(CScene*,	m_pPrevScene,		nullptr,		PrevScene)
	GETTOR_SETTOR	(CScene*,	m_pCurScene,		nullptr,		CurScene)
};
END

#endif
