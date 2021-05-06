#include "stdafx.h"
#include "ChangmoScene.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "TextManager.h"
#include "CollisionHelper.h"
#include "SceneManager.h"
#include "WndApp.h"
#include "MeshStore.h"
#include "BoundingVolume.h"
#include "CameraManager.h"
#include "Player.h"

CChangmoScene::CChangmoScene()
{
}


CChangmoScene::~CChangmoScene()
{
}

Engine::CScene* CChangmoScene::Create(void)
{
	CChangmoScene* pChangmoScene = new CChangmoScene;
	pChangmoScene->Awake((_int)ELayerID::NumOfLayerID);

	return pChangmoScene;
}

void CChangmoScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CChangmoScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CChangmoScene::Start(void)
{
	__super::Start();

	SP(Engine::CObject) spPlayerClone = Engine::ADD_CLONE(L"Player", true);
	//spPlayerClone->AddComponent<Engine::CDebugC>();
	//spPlayerClone->AddComponent<Engine::CCollisionC>()->
	//	AddCollider(Engine::CAabbCollider::Create(_float3(40, 75, 40), _float3(0, 37.5f, -5)));
	//spPlayerClone->GetComponent<Engine::CCollisionC>()->SetCollisionID(1);
	
	
	SP(Engine::CObject) spGridClone = Engine::ADD_CLONE(L"Grid", true);
	//spPlayerClone->AddComponent<Engine::CRigidBodyC>()->SetUseGravity(false);
	//spPlayerClone->AddComponent<Engine::CDebugC>();
	
	//SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Unit);
	//spBasicClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
	//spBasicClone->AddComponent<Engine::CTextureC>()->AddTexture(L"BlueBlock");
	//spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//spBasicClone->GetTransform()->SetSize(_float3(10, 10, 10));
	//spBasicClone->AddComponent<Engine::CCollisionC>()->
	//	AddCollider(Engine::CAabbCollider::Create(_float3(1, 1, 1)));
	//spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID(0);
	//
	//SP(Engine::CObject) spBasicClone1 = Engine::ADD_CLONE(L"BasicObject", true);
	//spBasicClone1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
	//spBasicClone1->AddComponent<Engine::CTextureC>()->AddTexture(L"BlueBlock");
	//spBasicClone1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//spBasicClone1->GetComponent<Engine::CTransformC>()->AddPositionX(3);
	//spBasicClone->GetTransform()->AddChild(spBasicClone1->GetTransform());
}

void CChangmoScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CChangmoScene::Update(void)
{
	__super::Update();
}

void CChangmoScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CChangmoScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CChangmoScene::OnEnable(void)
{

}

void CChangmoScene::OnDisable(void)
{
}

void CChangmoScene::InitPrototypes(void)
{
}