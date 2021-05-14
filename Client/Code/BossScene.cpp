#include "stdafx.h"
#include "BossScene.h"
#include "DataStore.h"
#include "ObjectFactory.h"
#include "TextManager.h"
#include "CameraManager.h"

#pragma region ObjectsHeader
#include "Player.h"
#include "MapObject.h"
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

	SP(Engine::CObject) spStageCollisionClone = 
		Engine::ADD_CLONE(L"EmptyObject", true, L"StageCollision", (_int)ELayerID::Map);

	spStageCollisionClone->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create(_float3(24, 1, 1.5f)));
	spStageCollisionClone->GetComponent<Engine::CCollisionC>()->SetCollisionID((_int)EColliderID::Map);
	//spStageCollisionClone->AddComponent<Engine::CDebugC>();
	spStageCollisionClone->GetTransform()->SetPosition(-8, -1.8f, 65.75f);
	

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
}
