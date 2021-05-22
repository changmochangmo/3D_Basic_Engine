#include "stdafx.h"
#include "CreditScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"
#include "FRC.h"
#include "CameraManager.h"

CCreditScene::CCreditScene()
{
}


CCreditScene::~CCreditScene()
{
}

Engine::CScene * CCreditScene::Create(void)
{
	CCreditScene* pInstance = new CCreditScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CCreditScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CCreditScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
}

void CCreditScene::Start(void)
{
	__super::Start();
	InitPrototypes();

	SP(Engine::CObject) spCameraObject = Engine::ADD_CLONE(L"Camera", this, true, L"BasicCamera", (_int)ELayerID::Camera);
	Engine::CCameraManager::GetInstance()->SetMainCamera(spCameraObject->GetComponent<Engine::CCameraC>());
	Engine::CCameraManager::GetInstance()->AddCamera(L"FreeCamera", spCameraObject->GetComponent<Engine::CCameraC>());

	{
		m_spCredit = Engine::ADD_CLONE(L"EmptyObject", this, true, L"", (_int)ELayerID::Map);
		m_spCredit->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		m_spCredit->GetTransform()->SetSize(800, 1200, 1);
		m_spCredit->AddComponent<Engine::CTextureC>()->AddTexture(L"Credit");
		m_spCredit->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		m_spCredit->GetTransform()->SetPositionY(-350);
	}
}

void CCreditScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CCreditScene::Update(void)
{
	__super::Update();
	m_spCredit->GetTransform()->AddPositionY(30 * GET_DT);
}

void CCreditScene::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CCreditScene::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CCreditScene::OnEnable(void)
{
}

void CCreditScene::OnDisable(void)
{
}

void CCreditScene::InitPrototypes(void)
{
}
