#include "stdafx.h"
#include "LogoScene.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "BossScene.h"

#include "UserInterface.h"
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
	
}

void CLogoScene::Start(void)
{
	__super::Start();
	InitPrototypes();
	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
		spBasicClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		spBasicClone->GetTransform()->SetSize(800, 400, 1);
		spBasicClone->AddComponent<Engine::CTextureC>()->AddTexture(L"Background");
		spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	}

	{
		SP(Engine::CObject) spTitleClone = Engine::ADD_CLONE(L"Title", false, L"", (_int)ELayerID::UI);
		SP(Engine::CObject) spPressAnyKeyClone = Engine::ADD_CLONE(L"PressAnyKey", false, L"", (_int)ELayerID::UI);

		//spPressAnyKeyClone->GetTransform()->SetGoalPosition(_float3(0, -190, 0));
		//spPressAnyKeyClone->GetTransform()->SetLerpOn(true);
		//spPressAnyKeyClone->GetTransform()->SetLerpSpeed(60);
	}

	
}

void CLogoScene::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CLogoScene::Update(void)
{
	__super::Update();
	
	if (Engine::IMKEY_DOWN(KEY_RIGHT))
		Engine::CSceneManager::GetInstance()->SceneChange(CBossScene::Create());
}

void CLogoScene::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CLogoScene::OnDestroy(void)
{
	__super::OnDestroy();
	
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
