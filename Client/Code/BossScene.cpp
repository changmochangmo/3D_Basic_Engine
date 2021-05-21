#include "stdafx.h"
#include "BossScene.h"
#include "DataStore.h"
#include "ObjectFactory.h"
#include "TextManager.h"
#include "CameraManager.h"

#pragma region ObjectsHeader
#include "Player.h"
#include "MapObject.h"

#include "Boss.h"
#include "RollerBlade.h"
#include "SandBag.h"
#include "MafiaBall.h"
#include "Decoration.h"
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
	for (_int i = 0; i < 6; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf", false);
		spCheeringMafClone->GetTransform()->SetPosition(-12.7f + 2 * i, -2.2f, 62.f);
	}
	for (_int i = 0; i < 5; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf1", false);
		spCheeringMafClone->GetTransform()->SetPosition(-11.7f + 2 * i, -2.2f, 62.f);
	}
	for (_int i = 0; i < 6; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf2", false);
		spCheeringMafClone->GetTransform()->SetPosition(-12.7f + 2 * i, -2.2f, 60.5f);
	}
	for (_int i = 0; i < 5; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf1", false);
		spCheeringMafClone->GetTransform()->SetPosition(-11.7f + 2 * i, -2.2f, 60.5f);
	}
	for (_int i = 0; i < 10; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf3", false);
		std::dynamic_pointer_cast<CDecoration>(spCheeringMafClone)->AddAnimationIndex(0);
		spCheeringMafClone->GetTransform()->SetPosition(-11.7f + i, -2.2f, 59.5f);
	}
	for (_int i = 0; i < 10; ++i)
	{
		SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf3", false);
		std::dynamic_pointer_cast<CDecoration>(spCheeringMafClone)->AddAnimationIndex(2);
		spCheeringMafClone->GetTransform()->SetPosition(-11.2f + i, -2.2f, 59.f);
	}

	SP(Engine::CObject) spCheeringMafClone = Engine::ADD_CLONE(L"CheeringMaf3", false);
	spCheeringMafClone->GetTransform()->SetRotationY(PI);
	spCheeringMafClone->GetTransform()->SetPosition(-8.7f, 2.05f, 70.5f);


	SP(Engine::CObject) spBossClone = Engine::ADD_CLONE(L"Boss", false);
	spBossClone->AddComponent<Engine::CDebugC>();

	SP(Engine::CObject) spPlayerClone = Engine::ADD_CLONE(L"Player", true);
	spPlayerClone->GetTransform()->SetPosition(-8, 1.8f, 65.75f);
	spPlayerClone->AddComponent<Engine::CDebugC>();

	_int numOfMapObject;
	Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects", L"numOfMapObject", numOfMapObject);
	for (_int i = 0; i < numOfMapObject; ++i)
	{
		SP(CMapObject) spLoadObject =
			std::dynamic_pointer_cast<CMapObject>(Engine::ADD_CLONE(L"MapObject", false));


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
		Engine::ADD_CLONE(L"EmptyObject", true, L"StageCollision0", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(24, 1, 5.5f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, -1.8f, 67.75f);

	//스테이지 왼쪽 벽
	spStageCollisionClone = 
		Engine::ADD_CLONE(L"EmptyObject", true, L"StageCollision1", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(1, 10, 3.75f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-16.4f, 3.2f, 66.86f);

	//스테이지 오른쪽 벽
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", true, L"StageCollision2", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(1, 10, 3.75f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(0.9f, 3.2f, 66.86f);

	//스테이지 뒤 오두막
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", true, L"StageCollision3", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(3.35f, 0.25, 3.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, 1.95f, 71.f);


	//스테이지 아래 관중석
	spStageCollisionClone =
		Engine::ADD_CLONE(L"EmptyObject", true, L"StageCollision4", (_int)ELayerID::Map);
	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(24.f, 1, 10.f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-7.7f, -3.3f, 60.f);

	
	__super::Start();
}

void CBossScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBossScene::Update(void)
{
	__super::Update();


	
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
	spMafiaDecoType4->GetComponent<Engine::CTextureC>()->AddTexture(L"mafia_face2_happy");
	spMafiaDecoType4->GetComponent<Engine::CTextureC>()->AddTexture(L"Map__6");
	spMafiaDecoType4->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	spMafiaDecoType4->AddAnimationIndex(1);
	Engine::ADD_PROTOTYPE(spMafiaDecoType4);
}
