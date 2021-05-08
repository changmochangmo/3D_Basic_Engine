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
	spPlayerClone->AddComponent<Engine::CDebugC>();
	//spPlayerClone->AddComponent<Engine::CCollisionC>()->
	//	AddCollider(Engine::CAabbCollider::Create(_float3(40, 75, 40), _float3(0, 37.5f, -5)));
	//spPlayerClone->GetComponent<Engine::CCollisionC>()->SetCollisionID(1);
	
	


	//SP(Engine::CObject) spGridClone = Engine::ADD_CLONE(L"Grid", true);
	//spPlayerClone->AddComponent<Engine::CRigidBodyC>()->SetUseGravity(false);
	//spPlayerClone->AddComponent<Engine::CDebugC>();
	
	SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Terrain);
	spBasicClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(10, 1, 10), _float3(0, -0.5, 0)));
	spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Terrain);
	spBasicClone->AddComponent<Engine::CDebugC>();

	_float3 right(1, 0, 1); D3DXVec3Normalize(&right, &right);
	_float3 forward(-1, 0, 1); D3DXVec3Normalize(&forward, &forward);
	_float3 up(0, 1, 0);
	SP(Engine::CObject) spBasicClone2 = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Terrain);
	spBasicClone2->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(1, 1, 1), _float3(0, 0.5, 0), right, up, forward));
	spBasicClone2->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Terrain);
	spBasicClone2->AddComponent<Engine::CDebugC>();
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