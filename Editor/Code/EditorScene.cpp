#include "stdafx.h"
#include "EditorScene.h"
#include "Object.h"
#include "ObjectFactory.h"

#include "InputManager.h"
#include "TextureStore.h"
#include "Layer.h"
#include "DataStore.h"

#include "MainFrm.h"
#include "EditorView.h"
#include "SceneManager.h"
#include "MenuView.h"

#include "Player.h"
#include "Grid.h"
#include "MapObject.h"
#include "MeshStore.h"
#include "MeshData.h"

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
	OnDestroy();
	delete this;
}

void CEditorScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();

	m_pMain			= dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pEditorView	= dynamic_cast<CEditorView*>(m_pMain->m_mainSplitter.GetPane(0, 0));
	m_pMenuView		= dynamic_cast<CMenuView*>(m_pMain->m_mainSplitter.GetPane(0, 1));

	//_int numOfMapObjects;
	//Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects", L"numOfMapObjects", numOfMapObjects);
	//
	//for (_int i = 0; i < numOfMapObjects; ++i)
	//{
	//	SP(Engine::CObject) spNewMapObject = Engine::ADD_CLONE(L"MapObject", false);
	//	spNewMapObject->
	//}
}

void CEditorScene::Start(void)
{
	__super::Start();
}

void CEditorScene::FixedUpdate(void)
{
}

void CEditorScene::Update(void)
{
	__super::Update();
	m_pMenuView->Update();
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
	SP(CMapObject) spBasicMapObject(CMapObject::Create());
	Engine::ADD_PROTOTYPE(spBasicMapObject);

	for (auto& mesh : Engine::CMeshStore::GetInstance()->GetCurSceneMeshData())
	{
		SP(CMapObject) spMapObject(CMapObject::Create());
		spMapObject->GetMesh()->AddMeshData(mesh.second->MakeClone());
		spMapObject->SetObjectKey(mesh.first);

		const std::vector<Engine::CMeshData*>& vMeshDatas = spMapObject->GetMesh()->GetMeshDatas();
		for (_size i = 0; i < vMeshDatas.size(); ++i)
		{
			const std::vector<std::wstring>& vTexList =  vMeshDatas[i]->GetTexList();
			for (_size j = 0; j < vTexList.size(); ++j)
			{
				spMapObject->GetTexture()->AddTexture(Engine::RemoveExtension(vTexList[j]), i);
			}
		}

		Engine::ADD_PROTOTYPE(spMapObject);
	}
}