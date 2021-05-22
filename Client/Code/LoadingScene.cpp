#include "stdafx.h"
#include "LoadingScene.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "InputManager.h"
#include "SceneManager.h"

#include "CameraManager.h"
#include "SceneManager.h"

#include "BossScene.h"

CLoadingScene::CLoadingScene()
{
}


CLoadingScene::~CLoadingScene()
{
}

Engine::CScene * CLoadingScene::Create(void)
{
	CLoadingScene* pInstance = new CLoadingScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CLoadingScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CLoadingScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
}

void CLoadingScene::Start(void)
{
	__super::Start();
	InitPrototypes();

	SP(Engine::CObject) spCameraObject = Engine::ADD_CLONE(L"Camera", true, L"BasicCamera", (_int)ELayerID::Camera);
	Engine::CCameraManager::GetInstance()->SetMainCamera(spCameraObject->GetComponent<Engine::CCameraC>());
	Engine::CCameraManager::GetInstance()->AddCamera(L"FreeCamera", spCameraObject->GetComponent<Engine::CCameraC>());

	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
		spBasicClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		spBasicClone->GetTransform()->SetSize(910, 512, 1);
		spBasicClone->AddComponent<Engine::CTextureC>()->AddTexture(L"Background");
		spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	}

	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
		spBasicClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		spBasicClone->GetTransform()->SetSize(60, 30, 1);
		spBasicClone->GetTransform()->SetPositionZ(-350);
		spBasicClone->AddComponent<Engine::CTextureC>()->AddTexture(L"Loading");
		spBasicClone->GetComponent<Engine::CTextureC>()->AddTexture(L"Complete");
		spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	}
}

void CLoadingScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CLoadingScene::Update(void)
{
	__super::Update();
}

void CLoadingScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CLoadingScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CLoadingScene::OnEnable(void)
{
	__super::OnEnable();
}

void CLoadingScene::OnDisable(void)
{
	__super::OnDisable();
}

void CLoadingScene::InitPrototypes(void)
{
}
