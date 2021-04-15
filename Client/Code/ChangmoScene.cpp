#include "stdafx.h"
#include "ChangmoScene.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "TextManager.h"
#include "CollisionHelper.h"
#include "SceneManager.h"
#include "WndApp.h"
#include "MeshStore.h"

CChangmoScene::CChangmoScene()
{
}


CChangmoScene::~CChangmoScene()
{
}

Engine::CScene* CChangmoScene::Create(void)
{
	CChangmoScene* pNewScene = new CChangmoScene;
	pNewScene->Awake((_int)ELayerID::NumOfLayerID);

	return pNewScene;
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
	spPlayerClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(1, 1, 1)));
	spPlayerClone->GetComponent<Engine::CCollisionC>()->SetCollisionID(1);
	spPlayerClone->AddComponent<Engine::CRigidBodyC>()->SetUseGravity(false);

	SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"BasicObject", true);
	spBasicClone->AddComponent<Engine::CMeshC>()->ChangeMesh(L"Cube");
	spBasicClone->AddComponent<Engine::CTextureC>()->ChangeTexture(L"None");
	spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::Base);
	spBasicClone->GetComponent<Engine::CTransformC>()->AddPositionX(3);
	spBasicClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(1, 1, 1)));
	spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID(0);
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