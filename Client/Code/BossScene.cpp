#include "stdafx.h"
#include "BossScene.h"
#include "DataStore.h"
#include "ObjectFactory.h"
#include "TextManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "FRC.h"

#pragma region ObjectsHeader
#include "Player.h"
#include "MapObject.h"
#include "UserInterface.h"

#include "Boss.h"
#include "RollerBlade.h"
#include "SandBag.h"
#include "MafiaBall.h"
#include "Decoration.h"
#include "Wall.h"
#include "Mafia.h"
#include "Cloud.h"
#include "JumpHat.h"
#include "FireHat.h"
#pragma endregion

CBossScene::CBossScene()
{
}


CBossScene::~CBossScene()
{
}

Engine::CScene * CBossScene::Create(void)
{
	CBossScene* pInstance = new CBossScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CBossScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CBossScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CBossScene::Start(void)
{
	SP(Engine::CObject) spCameraObject = Engine::ADD_CLONE(L"Camera", this, true, L"BasicCamera", (_int)ELayerID::Camera);
	m_spSceneCam = spCameraObject->GetComponent<Engine::CCameraC>();
	
	Engine::CCameraManager::GetInstance()->AddCamera(L"FreeCamera",
													 spCameraObject->GetComponent<Engine::CCameraC>());

	for (_int i = 0; i < 6; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf", this, false);
		spCheeringMafClone->GetTransform()->SetPosition(-12.7f + 2 * i, -3.8f, 64.f);
	}
	for (_int i = 0; i < 5; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf1", this, false);
		spCheeringMafClone->GetTransform()->SetPosition(-11.7f + 2 * i, -3.8f, 64.f);
	}
	for (_int i = 0; i < 6; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf2", this, false);
		spCheeringMafClone->GetTransform()->SetPosition(-12.7f + 2 * i, -3.8f, 62.5f);
	}
	for (_int i = 0; i < 5; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf1", this, false);
		spCheeringMafClone->GetTransform()->SetPosition(-11.7f + 2 * i, -3.8f, 62.5f);
	}
	for (_int i = 0; i < 10; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf3", this, false);
		std::dynamic_pointer_cast<CDecoration>(spCheeringMafClone)->AddAnimationIndex(0);
		spCheeringMafClone->GetTransform()->SetPosition(-11.7f + i, -3.8f, 61.5f);
	}
	for (_int i = 0; i < 10; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf3", this, false);
		std::dynamic_pointer_cast<CDecoration>(spCheeringMafClone)->AddAnimationIndex(2);
		spCheeringMafClone->GetTransform()->SetPosition(-11.2f + i, -3.8f, 61.f);
	}

	SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf3", this, false);
	spCheeringMafClone->GetTransform()->SetRotationY(PI);
	spCheeringMafClone->GetTransform()->SetPosition(-8.7f, 2.05f, 70.5f);


	SP(Engine::CObject) spBossClone = Engine::ADD_CLONE(L"Boss", this, false);
	//spBossClone->AddComponent<Engine::CDebugC>();

	SP(Engine::CObject) spPlayerClone = Engine::ADD_CLONE(L"Player", this, true);
	spPlayerClone->GetTransform()->SetPosition(-7.7f, 3.f, 27.f);
	//spPlayerClone->AddComponent<Engine::CDebugC>();
	m_spSceneCam->SetTarget(this->FindObjectWithKey(L"Player"));

	

#pragma region mapSetting
	_int numOfMapObject;
	Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects", L"numOfMapObject", numOfMapObject);
	for (_int i = 0; i < numOfMapObject; ++i)
	{
		SP(CMapObject) spLoadObject =
			std::dynamic_pointer_cast<CMapObject>(Engine::ADD_CLONE(L"MapObject", this, false));


		_int numOfMeshData;
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
			std::to_wstring(i) + L"_numOfMeshData", numOfMeshData);

		for (_int j = 0; j < numOfMeshData; ++j)
		{
			std::wstring meshKey;
			Engine::GET_VALUE(false, 
							  (_int)EDataID::Scene, L"MapObjects",
							  std::to_wstring(i) + L"_meshKey" + std::to_wstring(j),
							  meshKey);
			spLoadObject->GetMesh()->AddMeshData(meshKey);

			const std::vector<std::wstring>& texList = spLoadObject->GetMesh()->GetMeshDatas()[j]->GetTexList();
			for (_int k = 0; k < texList.size(); ++k)
				spLoadObject->GetTexture()->AddTexture(Engine::RemoveExtension(texList[k]), j);
		}

		_float3 position, rotation, size;
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
			std::to_wstring(i) + L"_position", position);
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
			std::to_wstring(i) + L"_rotation", rotation);
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
			std::to_wstring(i) + L"_size", size);

		SP(Engine::CTransformC) spTransform = spLoadObject->GetTransform();
		spTransform->SetPosition(position);
		spTransform->SetRotation(rotation);
		spTransform->SetSize(size);
	}

	//스테이지 바닥
	SP(Engine::CObject) spStageCollisionClone = 
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision0", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(24, 1, 5.5f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, -1.8f, 67.75f);

	//스테이지 왼쪽 벽
	spStageCollisionClone = 
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision1", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(1, 10, 3.75f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-16.4f, 3.2f, 66.86f);

	//스테이지 오른쪽 벽
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision2", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(1, 10, 3.75f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(0.9f, 3.2f, 66.86f);

	//스테이지 뒤 오두막
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision3", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(3.35f, 0.25, 3.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, 1.95f, 71.f);


	//스테이지 아래 관중석
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(24.f, 1, 10.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, -3.8f, 60.f);

	
	//극장 입구쪽
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(30.f, 1, 16.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, -1.f, 33.f);

	//극장2층
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(40.f, 1, 15.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, 5.7f, 29.5f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(10.2f, 1, 30.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->GetTransform()->SetPosition(-23.6f, 5.7f, 51.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(10.2f, 1, 30.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->GetTransform()->SetPosition(8.2f, 5.7f, 51.f);

	//극장3층
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(40.f, 1, 15.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, 13.25f, 29.5f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(10.2f, 1, 30.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->GetTransform()->SetPosition(-23.6f, 13.25f, 51.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(10.2f, 1, 30.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->GetTransform()->SetPosition(8.2f, 13.25f, 51.f);

	//극장 외벽
#pragma region TheaterWalls
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(5.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-11.f, 14.f, 26.f);
	spStageCollisionClone->GetTransform()->SetRotationY(PI * 10.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(5.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-4.4f, 14.f, 26.f);
	spStageCollisionClone->GetTransform()->SetRotationY(-PI * 10.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-15.5f, 14.f, 27.5f);
	spStageCollisionClone->GetTransform()->SetRotationY(PI * 20.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(0.1f, 14.f, 27.5f);
	spStageCollisionClone->GetTransform()->SetRotationY(-PI * 20.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-21.f, 14.f, 30.f);
	spStageCollisionClone->GetTransform()->SetRotationY(PI * 38.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(5.6f, 14.f, 30.f);
	spStageCollisionClone->GetTransform()->SetRotationY(-PI * 38.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-24.5f, 14.f, 34.f);
	spStageCollisionClone->GetTransform()->SetRotationY(PI * 54.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(9.1f, 14.f, 34.f);
	spStageCollisionClone->GetTransform()->SetRotationY(-PI * 54.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-26.5f, 14.f, 38.f);
	spStageCollisionClone->GetTransform()->SetRotationY(PI * 68.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(11.1f, 14.f, 38.f);
	spStageCollisionClone->GetTransform()->SetRotationY(-PI * 68.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-28.5f, 14.f, 43.f);
	spStageCollisionClone->GetTransform()->SetRotationY(PI * 82.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(6.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(13.1f, 14.f, 43.f);
	spStageCollisionClone->GetTransform()->SetRotationY(-PI * 82.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(14.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-29.f, 14.f, 51.f);
	spStageCollisionClone->GetTransform()->SetRotationY(PI * 90.f / 180.f);

	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", this, true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CObbCollider::Create(_float3(14.f, 30, 1.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(13.6f, 14.f, 51.f);
	spStageCollisionClone->GetTransform()->SetRotationY(-PI * 90.f / 180.f);
#pragma endregion

	SP(CWall) spWall = 
		std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-4.f, 14.f, 35.f);
	spWall->GetTransform()->SetRotationY(-15 * PI / 180.f);
	spWall->GetTransform()->SetSize(0.5f, 17, 4);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(0.5f, 17, 4));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(0.25f, 8.5f, 2));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-5.7f, 14.f, 33.f);
	spWall->GetTransform()->SetRotationY(-95 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-9.8f, 14.f, 33.2f);
	spWall->GetTransform()->SetRotationY(105 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-11.7f, 14.f, 35.f);
	spWall->GetTransform()->SetRotationY(15 * PI / 180.f);
	spWall->GetTransform()->SetSize(.5f, 17, 4);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(.5f, 17, 4));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(0.25f, 8.5f, 2));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	//
	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-1.5f, 14.f, 36.f);
	spWall->GetTransform()->SetRotationY(-30 * PI / 180.f);
	spWall->GetTransform()->SetSize(0.5f, 17, 4.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(.5f, 17, 4));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(0.25f, 8.5f, 2));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(0.8f, 14.f, 36.2f);
	spWall->GetTransform()->SetRotationY(50 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(4.f, 14.f, 39.2f);
	spWall->GetTransform()->SetRotationY(40 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(6.2f, 14.f, 42.7f);
	spWall->GetTransform()->SetRotationY(30 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(7.f, 14.f, 46.7f);
	spWall->GetTransform()->SetRotationY(0 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(11.f, 14.f, 48.7f);
	spWall->GetTransform()->SetRotationY(90 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 8.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 8));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 4));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);
	//

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-14.5f, 14.f, 36.f);
	spWall->GetTransform()->SetRotationY(35 * PI / 180.f);
	spWall->GetTransform()->SetSize(.5f, 17, 4);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(.5f, 17, 4));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(0.25f, 8.5f, 2));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-17.2f, 14.f, 36.8f);
	spWall->GetTransform()->SetRotationY(130 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-20.2f, 14.f, 40.4f);
	spWall->GetTransform()->SetRotationY(155 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-22.f, 14.f, 45.f);
	spWall->GetTransform()->SetRotationY(175 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 5.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 5));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 2.5f));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);

	spWall = std::dynamic_pointer_cast<CWall>(Engine::ADD_CLONE(L"Wall", this, false));
	spWall->GetTransform()->SetPosition(-26.4f, 14.f, 48.f);
	spWall->GetTransform()->SetRotationY(90 * PI / 180.f);
	spWall->GetTransform()->SetSize(1, 17, 8.f);
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetSize(_float3(1.f, 17, 8));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetHalfSize(_float3(.5f, 8.5, 4));
	static_cast<Engine::CObbCollider*>(spWall->GetCollision()->GetColliders()[0])->SetRadiusBS(8.5f);
	spWall->GetCollision()->SetRadiusBS(8.5f);
	//5.5
	Engine::ADD_CLONE(L"LifeText", this, false, L"", (_int)ELayerID::UI);
	Engine::ADD_CLONE(L"Clock", this, false, L"", (_int)ELayerID::UI);

	//오른쪽문
	Engine::ADD_CLONE(L"Door", this, false, L"", (_int)ELayerID::Map);
	//왼쪽
	SP(Engine::CObject) spDoor = Engine::ADD_CLONE(L"Door", this, false, L"", (_int)ELayerID::Map);
	spDoor->GetTransform()->SetSizeX(-0.013f);
	spDoor->GetTransform()->SetPositionX(-6.4f);
	spDoor->GetTransform()->SetPositionZ(25.1f);
#pragma endregion

	//시계
	m_firstDigit = 
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"Number", this, false, L"", (_int)ELayerID::UI));
	m_firstDigit->GetTransform()->AddRotationZ(PI / 4);
	m_firstDigit->GetTransform()->SetPosition(302.5f, -260.f, 0);
	m_firstDigit->GetTransform()->SetSize(60, 60, 0);

	m_secondDigit = 
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"Number", this, false, L"", (_int)ELayerID::UI));
	m_secondDigit->GetTransform()->AddRotationZ(PI / 4);
	m_secondDigit->GetTransform()->SetPosition(322.5, -240, 0);
	m_secondDigit->GetTransform()->SetSize(60, 60, 0);
	m_thirdDigit = 
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"Number", this, false, L"", (_int)ELayerID::UI));
	m_thirdDigit->GetTransform()->AddRotationZ(PI / 4);
	m_thirdDigit->GetTransform()->SetPosition(345.f, -227.5f, 0);
	m_thirdDigit->GetTransform()->SetSize(25, 25, 0);
	m_fourthDigit = 
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"Number", this, false, L"", (_int)ELayerID::UI));
	m_fourthDigit->GetTransform()->AddRotationZ(PI / 4);
	m_fourthDigit->GetTransform()->SetPosition(352.5f, -220.f, 0);
	m_fourthDigit->GetTransform()->SetSize(25, 25, 0);

	m_mouseUI =
		std::dynamic_pointer_cast<CUserInterface>(Engine::ADD_CLONE(L"Mouse", this, false, L"", (_int)ELayerID::UI));
	m_mouseUI->GetTransform()->AddRotationZ(-PI / 4);
	m_mouseUI->GetTransform()->SetSize(25, 25, 0);
	m_mouseUI->SetIsEnabled(false);
	
	SP(Engine::CObject) spMafiaClone = Engine::ADD_CLONE(L"Mafia", this, false);
	spMafiaClone->GetTransform()->SetPosition(-15, 1.5f, 40);
	spMafiaClone->GetTransform()->SetSize(0.02f, 0.02f, 0.02f);

	spMafiaClone = Engine::ADD_CLONE(L"Mafia", this, false);
	spMafiaClone->GetTransform()->SetPosition(-0.36f, 1.5f, 40);
	spMafiaClone->GetTransform()->SetSize(0.02f, 0.02f, 0.02f);

	//앉아있는 마피아들
	SP(CDecoration) spRedSuitClone = 
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-11.4f, -0.5f, 41);
	spRedSuitClone->AddAnimationIndex(2);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-10.3f, -0.5f, 41);
	spRedSuitClone->AddAnimationIndex(1);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-6.2f, -0.5f, 41);
	spRedSuitClone->AddAnimationIndex(2);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-8.25f, -0.9f, 42.5f);
	spRedSuitClone->AddAnimationIndex(1);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-7.225f, -0.9f, 42.5f);
	spRedSuitClone->AddAnimationIndex(1);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-2.f, -0.9f, 42.5f);
	spRedSuitClone->AddAnimationIndex(2);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-2.f, -1.9f, 46.2f);
	spRedSuitClone->AddAnimationIndex(2);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-3.025f, -1.9f, 46.2f);
	spRedSuitClone->AddAnimationIndex(0);

	spRedSuitClone =
	std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-11.4f, -1.9f, 46.2f);
	spRedSuitClone->AddAnimationIndex(2);

	spRedSuitClone =
		std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
	spRedSuitClone->GetTransform()->SetPosition(-10.3f, -1.9f, 46.2f);
	spRedSuitClone->AddAnimationIndex(1);




	for (_int i = 0; i < 12; ++i)
	{
		spRedSuitClone =
			std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
		spRedSuitClone->GetTransform()->SetPosition(-13.52f + i * 1.04, -2.5f, 52.0f);
		spRedSuitClone->AddAnimationIndex(i % 3);
	}

	for (_int i = 0; i < 12; ++i)
	{
		spRedSuitClone =
			std::dynamic_pointer_cast<CDecoration>(Engine::ADD_CLONE(L"RedSuit", this, false));
		spRedSuitClone->GetTransform()->SetPosition(-13.52f + i * 1.04, -2.9f, 53.4f);
		spRedSuitClone->AddAnimationIndex((i + 1)%3);
	}

	SP(CCloud) spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-7.7f, 3.f, 40.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-4.7f, 6.f, 40.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-8.7f, 6.f, 43.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-12.7f, 7.f, 43.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-12.7f, 7.f, 47.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-9.7f, 4.f, 43.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-2.7f, 7.f, 46.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-14.7f, 4.f, 54.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(-5.7f, 3.f, 55.f);

	spCloudClone =
		std::dynamic_pointer_cast<CCloud>(Engine::ADD_CLONE(L"Cloud", this, false));
	spCloudClone->GetTransform()->SetPosition(0.7f, 3.f, 52.f);

	__super::Start();
}

void CBossScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBossScene::Update(void)
{
	__super::Update();

	if (m_timeLeft >= 99.99f)
		m_timeLeft = 99.99f;
	if (m_timeLeft < 0)
		m_timeLeft = 0;
	_int firstDigit = (_int)(m_timeLeft / 10) % 10;
	_int secondDigit = (_int)(m_timeLeft) % 10;
	_int thirdDigit = (_int)(m_timeLeft * 10) % 10;
	_int fourthDigit = (_int)(m_timeLeft * 100) % 10;
	
	m_firstDigit->GetTexture()->SetTexIndex(firstDigit);
	m_secondDigit->GetTexture()->SetTexIndex(secondDigit);
	m_thirdDigit->GetTexture()->SetTexIndex(thirdDigit);
	m_fourthDigit->GetTexture()->SetTexIndex(fourthDigit);
	
	m_timeLeft -= GET_DT;


	m_mouseUI->GetTransform()->SetPosition(Engine::CInputManager::GetInstance()->GetMousePos());
}

void CBossScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBossScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CBossScene::OnEnable(void)
{
	__super::OnEnable();
}

void CBossScene::OnDisable(void)
{
	__super::OnDisable();
}

void CBossScene::InitPrototypes(void)
{
	{
		SP(CUserInterface) spLifeUIPrototype(CUserInterface::Create(L"PlayerLife"));
		Engine::ADD_PROTOTYPE(spLifeUIPrototype);

		SP(CUserInterface) spLifeTextUIPrototype(CUserInterface::Create(L"LifeText"));
		Engine::ADD_PROTOTYPE(spLifeTextUIPrototype);

		SP(CUserInterface) spClockUIPrototype(CUserInterface::Create(L"Clock"));
		Engine::ADD_PROTOTYPE(spClockUIPrototype);

		SP(CUserInterface) spNumberUIPrototype(CUserInterface::Create(L"Number"));
		Engine::ADD_PROTOTYPE(spNumberUIPrototype);

		SP(CUserInterface) spMouseUIPrototype(CUserInterface::Create(L"Mouse"));
		Engine::ADD_PROTOTYPE(spMouseUIPrototype);
	}

	SP(Engine::CObject) spBossPrototype(CBoss::Create(false));
	Engine::ADD_PROTOTYPE(spBossPrototype);

	SP(Engine::CObject) spRollerBladePrototype(CRollerBlade::Create(false));
	Engine::ADD_PROTOTYPE(spRollerBladePrototype);

	SP(Engine::CObject) spSandBagPrototype(CSandBag::Create(false));
	Engine::ADD_PROTOTYPE(spSandBagPrototype);

	SP(Engine::CObject) spMafiaBallPrototype(CMafiaBall::Create(false));
	Engine::ADD_PROTOTYPE(spMafiaBallPrototype);

	SP(CDecoration) spMafiaDecoType1(CDecoration::Create(false));
	spMafiaDecoType1->SetObjectKey(L"CheeringMaf");
	spMafiaDecoType1->SetLayerID((_int)ELayerID::Map);
	spMafiaDecoType1->GetTransform()->SetSize(0.01f, 0.01f, 0.01f);
	spMafiaDecoType1->GetComponent<Engine::CMeshC>()->AddMeshData(L"Mafia");
	spMafiaDecoType1->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_body_texture");
	spMafiaDecoType1->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_face2_happy");
	spMafiaDecoType1->GetComponent<Engine::CTextureC>()->AddTexture(L"Map__6");
	spMafiaDecoType1->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	spMafiaDecoType1->AddAnimationIndex(4);
	spMafiaDecoType1->AddAnimationIndex(3);
	spMafiaDecoType1->AddAnimationIndex(5);
	Engine::ADD_PROTOTYPE(spMafiaDecoType1);

	SP(CDecoration) spMafiaDecoType2(CDecoration::Create(false));
	spMafiaDecoType2->SetObjectKey(L"CheeringMaf1");
	spMafiaDecoType2->SetLayerID((_int)ELayerID::Map);
	spMafiaDecoType2->GetTransform()->SetSize(0.01f, 0.01f, 0.01f);
	spMafiaDecoType2->GetComponent<Engine::CMeshC>()->AddMeshData(L"Mafia");
	spMafiaDecoType2->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_body_texture");
	spMafiaDecoType2->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_face2_happy");
	spMafiaDecoType2->GetComponent<Engine::CTextureC>()->AddTexture(L"Map__6");
	spMafiaDecoType2->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	spMafiaDecoType2->AddAnimationIndex(3);
	spMafiaDecoType2->AddAnimationIndex(5);
	Engine::ADD_PROTOTYPE(spMafiaDecoType2);

	SP(CDecoration) spMafiaDecoType3(CDecoration::Create(false));
	spMafiaDecoType3->SetObjectKey(L"CheeringMaf2");
	spMafiaDecoType3->SetLayerID((_int)ELayerID::Map);
	spMafiaDecoType3->GetTransform()->SetSize(0.01f, 0.01f, 0.01f);
	spMafiaDecoType3->GetComponent<Engine::CMeshC>()->AddMeshData(L"Mafia");
	spMafiaDecoType3->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_body_texture");
	spMafiaDecoType3->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_face2_happy");
	spMafiaDecoType3->GetComponent<Engine::CTextureC>()->AddTexture(L"Map__6");
	spMafiaDecoType3->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	spMafiaDecoType3->AddAnimationIndex(5);
	spMafiaDecoType3->AddAnimationIndex(3);
	Engine::ADD_PROTOTYPE(spMafiaDecoType3);

	SP(CDecoration) spMafiaDecoType4(CDecoration::Create(false));
	spMafiaDecoType4->SetObjectKey(L"CheeringMaf3");
	spMafiaDecoType4->SetLayerID((_int)ELayerID::Map);
	spMafiaDecoType4->GetTransform()->SetSize(0.01f, 0.01f, 0.01f);
	spMafiaDecoType4->GetComponent<Engine::CMeshC>()->AddMeshData(L"Mafia");
	spMafiaDecoType4->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_body_texture");
	spMafiaDecoType4->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_face2_sleepy");
	spMafiaDecoType4->GetComponent<Engine::CTextureC>()->AddTexture(L"Map__6");
	spMafiaDecoType4->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	spMafiaDecoType4->AddAnimationIndex(1);
	Engine::ADD_PROTOTYPE(spMafiaDecoType4);

	SP(CDecoration) spRedSuitPrototype(CDecoration::Create(false));
	spRedSuitPrototype->SetObjectKey(L"RedSuit");
	spRedSuitPrototype->SetLayerID((_int)ELayerID::Map);
	spRedSuitPrototype->GetTransform()->SetSize(0.01f, 0.01f, 0.01f);
	spRedSuitPrototype->GetComponent<Engine::CMeshC>()->AddMeshData(L"Mafia_B");
	spRedSuitPrototype->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_body_purple");
	spRedSuitPrototype->GetComponent<Engine::CTextureC>()->AddTexture(L"Map__16");
	spRedSuitPrototype->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_face2_sleepy");
	
	spRedSuitPrototype->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	Engine::ADD_PROTOTYPE(spRedSuitPrototype);


	SP(CDecoration) spDoorPrototype(CDecoration::Create(false));
	spDoorPrototype->SetObjectKey(L"Door");
	spDoorPrototype->SetLayerID((_int)ELayerID::Map);
	spDoorPrototype->GetTransform()->SetSize(0.013f, 0.011f, 0.01f);
	spDoorPrototype->GetTransform()->SetPosition(-9.f, -0.5f, 25.f);
	spDoorPrototype->GetComponent<Engine::CMeshC>()->AddMeshData(L"Door");
	spDoorPrototype->GetComponent<Engine::CTextureC>()->AddTexture(L"radio_hole_gold");
	spDoorPrototype->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	Engine::ADD_PROTOTYPE(spDoorPrototype);


	SP(CWall) spWallPrototype(CWall::Create(false));
	Engine::ADD_PROTOTYPE(spWallPrototype);

	SP(CMafia) spMafiaPrototype(CMafia::Create(false));
	Engine::ADD_PROTOTYPE(spMafiaPrototype);

	SP(CCloud) spCloudPrototype(CCloud::Create(false));
	Engine::ADD_PROTOTYPE(spCloudPrototype);

	SP(CJumpHat) spJumpHat(CJumpHat::Create(false));
	Engine::ADD_PROTOTYPE(spJumpHat);

	SP(CFireHat) spFireHat(CFireHat::Create(false));
	Engine::ADD_PROTOTYPE(spFireHat);
}
