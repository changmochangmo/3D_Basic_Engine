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
#include "UserInterface.h"
CChangmoScene::CChangmoScene()
{
}


CChangmoScene::~CChangmoScene()
{
}

Engine::CScene* CChangmoScene::Create(void)
{
	CChangmoScene* pInstance = new CChangmoScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CChangmoScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CChangmoScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	
}

void CChangmoScene::Start(void)
{
	__super::Start();
	InitPrototypes();
	SP(Engine::CObject) spPlayerClone = Engine::ADD_CLONE(L"Player", true);
	spPlayerClone->AddComponent<Engine::CDebugC>();
	//spPlayerClone->AddComponent<Engine::CCollisionC>()->
	//	AddCollider(Engine::CAabbCollider::Create(_float3(40, 75, 40), _float3(0, 37.5f, -5)));
	//spPlayerClone->GetComponent<Engine::CCollisionC>()->SetCollisionID(1);


	SP(Engine::CObject) spWhatever = Engine::ADD_CLONE(L"Background", false);

	//SP(Engine::CObject) spGridClone = Engine::ADD_CLONE(L"Grid", true);
	//spPlayerClone->AddComponent<Engine::CRigidBodyC>()->SetUseGravity(false);
	//spPlayerClone->AddComponent<Engine::CDebugC>();

	//콜리젼 AABB
	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
		spBasicClone->AddComponent<Engine::CCollisionC>()->
			AddCollider(Engine::CAabbCollider::Create(_float3(10, 1, 10), _float3(0, 0, 0)));
		spBasicClone->GetTransform()->SetPosition(0, -0.5, 0);
		spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
		spBasicClone->AddComponent<Engine::CDebugC>();
	}
	
	//콜리젼 AABB2
	for(_int i = 0; i < 1; ++i)
	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
		spBasicClone->GetTransform()->SetPosition(0, 0.5, 3);
		spBasicClone->GetTransform()->SetRotationX(PI / 8.f);
		spBasicClone->AddComponent<Engine::CCollisionC>()->
			AddCollider(Engine::CObbCollider::Create(_float3(1, 1, 1), ZERO_VECTOR, RIGHT_VECTOR,
				UP_VECTOR, FORWARD_VECTOR));
		spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
		spBasicClone->AddComponent<Engine::CDebugC>();
	}

	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
		spBasicClone->GetTransform()->SetPositionY(2.5);
		spBasicClone->AddComponent<Engine::CCollisionC>()->
			AddCollider(Engine::CAabbCollider::Create(_float3(1, 1, 1), _float3(0, 0, 0)));
		spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
		spBasicClone->AddComponent<Engine::CDebugC>();
	}

	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
		spBasicClone->GetTransform()->SetPosition(-1, 0.5, 0);
		spBasicClone->AddComponent<Engine::CCollisionC>()->
			AddCollider(Engine::CAabbCollider::Create(_float3(1, 1, 1), _float3(0, 0, 0)));
		spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
		spBasicClone->AddComponent<Engine::CDebugC>();
	}

	//빨간점
	//{
	//	SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
	//	spBasicClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Sphere");
	//	spBasicClone->AddComponent<Engine::CTextureC>()->AddTexture(L"RedBlock");
	//	spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	//	spBasicClone->GetTransform()->SetSize(_float3(0.05f, 0.05f, 0.05f));
	//}
	//
	//{
	//	SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", true, L"", (_int)ELayerID::Map);
	//	spBasicClone->AddComponent<Engine::CMeshC>()->AddMeshData(L"Sphere");
	//	spBasicClone->AddComponent<Engine::CTextureC>()->AddTexture(L"BlueBlock");
	//	spBasicClone->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	//	spBasicClone->GetTransform()->SetSize(_float3(0.05f, 0.05f, 0.05f));
	//}
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
	__super::OnEnable();
}

void CChangmoScene::OnDisable(void)
{
	__super::OnDisable();
}

void CChangmoScene::InitPrototypes(void)
{
	//SP(CUserInterface) spUIPrototype(CUserInterface::Create(L"Background"));
	//Engine::ADD_PROTOTYPE(spUIPrototype);
}