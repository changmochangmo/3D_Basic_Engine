#include "stdafx.h"
#include "EditorScene.h"
#include "Object.h"
#include "ObjectFactory.h"

#include "InputManager.h"
#include "TextureStore.h"
#include "Layer.h"
#include "MainFrm.h"
#include "ObjectListView.h"
#include "EditorView.h"
#include "SceneManager.h"
#include "MenuView.h"

CEditorScene::CEditorScene()
{
}

CEditorScene::~CEditorScene()
{
}

Engine::CScene* CEditorScene::Create(void)
{
	Engine::CScene* pEditorScene = new CEditorScene;
	pEditorScene->Awake((_int)ELayerID::NumOfLayerID);

	return pEditorScene;
}

void CEditorScene::Free(void)
{
}

void CEditorScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CEditorScene::Start(void)
{
	__super::Start();

	m_pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pEditorView = dynamic_cast<CEditorView*>(m_pMain->m_mainSplitter.GetPane(0, 0));
	m_pMenuView = dynamic_cast<CMenuView*>(m_pMain->m_mainSplitter.GetPane(0, 1));
	//m_pListView = dynamic_cast<CObjectListView*>(m_pMain->m_uiSplitter.GetPane(0, 0));


}

void CEditorScene::FixedUpdate(void)
{
}

void CEditorScene::Update(void)
{
	__super::Update();

}

void CEditorScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEditorScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CEditorScene::OnEnable(void)
{
}

void CEditorScene::OnDisable(void)
{
}


void CEditorScene::InitPrototypes(void)
{
}

