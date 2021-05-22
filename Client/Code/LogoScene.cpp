#include "stdafx.h"
#include "LogoScene.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "CameraManager.h"
#include "SceneManager.h"

#include "UserInterface.h"
#include "Loading.h"
CLogoScene::CLogoScene()
{
}


CLogoScene::~CLogoScene()
{
}

Engine::CScene * CLogoScene::Create(void)
{
	CLogoScene* pInstance = new CLogoScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CLogoScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CLogoScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	m_pLoading = CLoading::Create((_int)ELoadingID::BossSceneResource);
}

void CLogoScene::Start(void)
{
	__super::Start();
	InitPrototypes();

	SP(Engine::CObject) spCameraObject = Engine::ADD_CLONE(L"Camera", this, true, L"BasicCamera", (_int)ELayerID::Camera);
	Engine::CCameraManager::GetInstance()->SetMainCamera(spCameraObject->GetComponent<Engine::CCameraC>());
	Engine::CCameraManager::GetInstance()->AddCamera(L"FreeCamera", spCameraObject->GetComponent<Engine::CCameraC>());

	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", this, true, L"", (_int)ELayerID::Map);
		spBasicClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		spBasicClone->GetTransform()->SetSize(800, 400, 1);
		spBasicClone->AddComponent<Engine::CTextureC>()->AddTexture(L"Background");
		spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	}

	{
		SP(Engine::CObject) spTitleClone = Engine::ADD_CLONE(L"Title", this, false, L"", (_int)ELayerID::UI);
		m_pPressAny= Engine::ADD_CLONE(L"PressAnyKey", this, false, L"", (_int)ELayerID::UI);

		
	}

	
}

void CLogoScene::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CLogoScene::Update(void)
{
	__super::Update();
	
	if (m_pLoading->GetFinish())
	{
		if (m_pPressAny->GetTransform()->GetPosition().y == -500)
		{
			m_pPressAny->GetTransform()->SetGoalPosition(_float3(0, -190, 0));
			m_pPressAny->GetTransform()->SetLerpOn(true);
			m_pPressAny->GetTransform()->SetLerpSpeed(100);
		}
		if (Engine::IMKEY_DOWN(KEY_RIGHT))
		{
			Engine::CSceneManager::GetInstance()->SceneChange(m_pLoading->GetNextScene(), true);
		}
	}
	
}

void CLogoScene::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CLogoScene::OnDestroy(void)
{
	__super::OnDestroy();
	delete m_pLoading;
}

void CLogoScene::OnEnable(void)
{
	__super::OnEnable();
	
}

void CLogoScene::OnDisable(void)
{
	__super::OnDisable();
	
}

void CLogoScene::InitPrototypes(void)
{
	SP(CUserInterface) spTitlePrototype(CUserInterface::Create(L"Title"));
	spTitlePrototype->GetTexture()->SetChangeTex(true);
	Engine::ADD_PROTOTYPE(spTitlePrototype);

	SP(CUserInterface) spPressAnyButtonPrototype(CUserInterface::Create(L"PressAnyKey"));
	Engine::ADD_PROTOTYPE(spPressAnyButtonPrototype);
}
