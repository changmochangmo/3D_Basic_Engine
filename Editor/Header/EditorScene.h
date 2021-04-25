#pragma once
#include "Scene.h"

class CEditorScene final : public Engine::CScene
{
private:
	explicit							CEditorScene		(void);
									   ~CEditorScene		(void);

public:
	static			Engine::CScene*		Create				(void);
					void				Free				(void) override;

					void				Awake				(_int numOfLayers) override;
					void				Start				(void) override;
															   
					void				FixedUpdate			(void) override;
					void				Update				(void) override;
					void				LateUpdate			(void) override;	
					
					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;	 
					void				OnDisable			(void) override;

private:
					void				InitPrototypes		(void) override;


private:
	_bool m_isPickingMode = false;
	_bool m_AddFistCubeToListBox = true;
	class Engine::CObject* m_pPreSelectedObject = nullptr;
	class Engine::CObject* m_pCurSelectedObject = nullptr;

	class CMainFrame * m_pMain;
	class CEditorView* m_pEditorView;
	class CObjectListView* m_pListView;
	class CMenuView*		m_pMenuView;
};

