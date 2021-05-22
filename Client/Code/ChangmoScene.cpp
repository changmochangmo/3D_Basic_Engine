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
#include "Wall.h"
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
	InitPrototypes();
}

void CChangmoScene::Start(void)
{
	SP(Engine::CObject) spCameraObject = Engine::ADD_CLONE(L"Camera", this, true, L"BasicCamera", (_int)ELayerID::Camera);
	m_spSceneCam = spCameraObject->GetComponent<Engine::CCameraC>();

	Engine::CCameraManager::GetInstance()->AddCamera(L"FreeCamera",
		spCameraObject->GetComponent<Engine::CCameraC>());
	Engine::CCameraManager::GetInstance()->SetMainCamera(m_spSceneCam);

	__super::Start();
	
	SP(Engine::CObject) spPlayerClone = Engine::ADD_CLONE(L"Player", this, true);
	spPlayerClone->AddComponent<Engine::CDebugC>();
	m_spSceneCam->SetTarget(this->FindObjectWithKey(L"Player"));
	//spPlayerClone->AddComponent<Engine::CCollisionC>()->
	//	AddCollider(Engine::CAabbCollider::Create(_float3(40, 75, 40), _float3(0, 37.5f, -5)));
	//spPlayerClone->GetComponent<Engine::CCollisionC>()->SetCollisionID(1);

	SP(CWall) spWall =
		std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(0.f, 0.f, 0.f);
	spWall->GetTransform()->SetRotationY(-15 * PI / 180.f);
	spWall->GetTransform()->SetSize(0.5f, 17, 4);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(0.5f, 17, 4));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(0.25f, 8.5f, 2));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);
	

	//SP(Engine::CObject) spGridClone = Engine::ADD_CLONE(L"Grid", true);
	//spPlayerClone->AddComponent<Engine::CRigidBodyC>()->SetUseGravity(false);
	//spPlayerClone->AddComponent<Engine::CDebugC>();

	//콜리젼 AABB
	{
		SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", this, true, L"", (_int)ELayerID::Map);
		spBasicClone->AddComponent<Engine::CCollisionC>()->
			AddCollider(Engine::CAabbCollider::Create(_float3(10, 1, 10), _float3(0, 0, 0)));
		spBasicClone->GetTransform()->SetPosition(0, -0.5, 0);
		spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
		spBasicClone->AddComponent<Engine::CDebugC>();
	}
	
	//콜리젼 AABB2
	//for(_int i = 0; i < 1; ++i)
	//{
	//	SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", this, true, L"", (_int)ELayerID::Map);
	//	spBasicClone->GetTransform()->SetPosition(0, 0.5, 3);
	//	spBasicClone->GetTransform()->SetRotationX(PI / 8.f);
	//	spBasicClone->AddComponent<Engine::CCollisionC>()->
	//		AddCollider(Engine::CObbCollider::Create(_float3(1, 1, 1), ZERO_VECTOR, RIGHT_VECTOR,
	//			UP_VECTOR, FORWARD_VECTOR));
	//	spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	//	spBasicClone->AddComponent<Engine::CDebugC>();
	//}
	//
	//{
	//	SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", this, true, L"", (_int)ELayerID::Map);
	//	spBasicClone->GetTransform()->SetPositionY(2.5);
	//	spBasicClone->AddComponent<Engine::CCollisionC>()->
	//		AddCollider(Engine::CAabbCollider::Create(_float3(1, 1, 1), _float3(0, 0, 0)));
	//	spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	//	spBasicClone->AddComponent<Engine::CDebugC>();
	//}
	//
	//{
	//	SP(Engine::CObject) spBasicClone = Engine::ADD_CLONE(L"EmptyObject", this, true, L"", (_int)ELayerID::Map);
	//	spBasicClone->GetTransform()->SetPosition(-1, 0.5, 0);
	//	spBasicClone->AddComponent<Engine::CCollisionC>()->
	//		AddCollider(Engine::CAabbCollider::Create(_float3(1, 1, 1), _float3(0, 0, 0)));
	//	spBasicClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	//	spBasicClone->AddComponent<Engine::CDebugC>();
	//}
	//
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

	SP(CWall) spWallPrototype(CWall::Create(false));
	Engine::ADD_PROTOTYPE(spWallPrototype);
}