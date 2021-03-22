#include "stdafx.h"
#include "ChangmoScene.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "FontManager.h"
#include "CollisionHelper.h"
#include "YellowBlockComponent.h"
#include "SceneManager.h"
#include "WndApp.h"

CChangmoScene::CChangmoScene()
{
}


CChangmoScene::~CChangmoScene()
{
}

SHARED(Engine::CScene) CChangmoScene::Create(void)
{
	SHARED(CChangmoScene) pCLogoScene(new CChangmoScene, Engine::SmartDeleter<CChangmoScene>);

	return pCLogoScene;
}

void CChangmoScene::Awake(void)
{
	__super::Awake();
	InitLayers();
	InitPrototypes();
}

void CChangmoScene::Start(void)
{
	__super::Start();

	Engine::ADD_TEXT(L"WOWOW", L"한글을 쓸 수 있어", _float3(10, 10, 0), D3DXCOLOR(0, 0, 0, 1));

	/********** Player **********/
	SHARED(Engine::CGameObject) pPlayer = Engine::ADD_CLONE(L"Player", L"Player", true);
	pPlayer->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0.f, 1.f, 4.f));
	pPlayer->SetName(L"Player");

	SHARED(Engine::CGameObject) pEnemy = Engine::ADD_CLONE(L"Enemy", L"Enemy", true);
	pEnemy->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0.f, 0.f, 4.f));
	pEnemy->GetComponent<CEnemyComponent>()->SetPlayerTransform(pPlayer->GetComponent<Engine::CTransformComponent>());
	pEnemy->SetName(L"Enemy");

	/********** Camera **********/
	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();

	///********** White Block **********/
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{	
			if ((5 == i && j == 0) ||
				0 == i && 0 == j ||
				2 == i && 3 == j ||
				3 == i && 3 == j ||
				4 == i && 3 == j)
				continue;
			SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(i * 1.f, 0, j * 1.f));
		}
	}

	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(5, 3, 6));

	pObj = Engine::ADD_CLONE(L"NormalBlock", L"WhiteBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(4, 3, 3));

	pObj = Engine::ADD_CLONE(L"NormalBlock", L"WhiteBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 0, 0));

	///********** Red Block **********/
	//pObj = Engine::ADD_CLONE(L"EventBlock", L"RedBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(2, 0, -1));

	////pObj = Engine::ADD_CLONE(L"EventBlock", L"RedBlock", true);
	////pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 1, -2));
	////pObj->GetComponent<Engine::CTransformComponent>()->SetRotation({ D3DXToRadian(90.f), 0.f, 0.f });

	///********** Blue Block **********/
	//pObj = Engine::ADD_CLONE(L"EventBlock", L"BlueBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(5, 0, 0));

	///********** Yellow Block **********/
	//pObj = Engine::ADD_CLONE(L"EventBlock", L"YellowBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(2, -1, 3));

	//pObj = Engine::ADD_CLONE(L"EventBlock", L"YellowBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(3, -1, 3));

	//pObj = Engine::ADD_CLONE(L"EventBlock", L"YellowBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(4, -1, 3));

	////////
	//pObj = Engine::ADD_CLONE(L"EventBlock", L"YellowBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 1, 5));
	//pObj->GetComponent<Engine::CTransformComponent>()->SetRotationX(D3DXToRadian(90));

	//pObj = Engine::ADD_CLONE(L"EventBlock", L"YellowBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1, 2, 5));
	//pObj->GetComponent<Engine::CTransformComponent>()->SetRotationX(D3DXToRadian(90));

	//pObj = Engine::ADD_CLONE(L"EventBlock", L"YellowBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(2, 3, 5));
	//pObj->GetComponent<Engine::CTransformComponent>()->SetRotationX(D3DXToRadian(90));

	///********** Green Block **********/
	//pObj = Engine::ADD_CLONE(L"EventBlock", L"GreenBlock", true);
	//pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 100, 0));

	////pObj = Engine::ADD_CLONE(L"EventBlock", L"GreenBlock", true);
	////pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(5, 5, 0));
	
	Stage2Load();

	/********** Mouse UI **********/
	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(10.0f, 10.0f, 1.0f));
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 0, 1));
		pObj->AddComponent<Engine::CUIComponent>()->SetTextureKey(L"MousePointUI");
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"UI", L"Test", true);
		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(0, 0, 5));
	}
}

_uint CChangmoScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return _uint();
}

_uint CChangmoScene::Update(void)
{
	//__super::Update();

	_uint event = NO_EVENT;
	if (event = __super::Update())
		return event;

	return event;
}

_uint CChangmoScene::LateUpdate(void)
{
	__super::LateUpdate();

	_uint event = NO_EVENT;
	if (event = __super::LateUpdate())
		return event;


	return event;
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

void CChangmoScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"Enemy");
	AddLayer(L"NormalBlock");
	AddLayer(L"EventBlock");
	AddLayer(L"Default");
	AddLayer(L"UI");
}

void CChangmoScene::InitPrototypes(void)
{
}

HRESULT CChangmoScene::Stage2Load()
{
	std::string filePath = "../../Data/Save_1.txt";
	std::ifstream ifsLoad(filePath.data());
	Engine::CSceneManager::GetInstance()->GetUnitInfo().clear();

	if (ifsLoad.is_open())
	{
		std::string line;

		while (!ifsLoad.eof())
		{
			std::string ObjectKey;

			if (std::getline(ifsLoad, line))
				ObjectKey = line;
			else
				break;

			float xPos = 0.f, yPos = 0.f, zPos = 0.f;
			float xRot = 0.f, yRot = 0.f, zRot = 0.f;


			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr(line);
				ssr >> xPos;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr2(line);
				ssr2 >> yPos;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr3(line);
				ssr3 >> zPos;
			}
			else
				break;
			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr4(line);
				ssr4 >> xRot;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr5(line);
				ssr5 >> yRot;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr6(line);
				ssr6 >> zRot;
			}
			else
				break;

			Engine::UNITINFO vInfo;


			if (ObjectKey == "m_objectKey=WhiteBlock")
			{
				vInfo.vPos = _float3(xPos, yPos, zPos);
				vInfo.vRot = _float3(xRot, yRot, zRot);

				vInfo.wsObjectKey = L"WhiteBlock";
			}
			else if (ObjectKey == "m_objectKey=RedBlock")
			{
				vInfo.vPos = _float3(xPos, yPos, zPos);
				vInfo.vRot = _float3(xRot, yRot, zRot);

				vInfo.wsObjectKey = L"RedBlock";
			}
			else if (ObjectKey == "m_objectKey=BlueBlock")
			{
				vInfo.vPos = _float3(xPos, yPos, zPos);
				vInfo.vRot = _float3(xRot, yRot, zRot);

				vInfo.wsObjectKey = L"BlueBlock";
			}
			else if (ObjectKey == "m_objectKey=YellowBlock")
			{
				vInfo.vPos = _float3(xPos, yPos, zPos);
				vInfo.vRot = _float3(xRot, yRot, zRot);

				vInfo.wsObjectKey = L"YellowBlock";
			}

			Engine::CSceneManager::GetInstance()->GetUnitInfo().emplace_back(vInfo);
		}
	}
	else
	{
		MessageBox(Engine::CWndApp::GetInstance()->GetHWnd(), L"Load Failed", L"Failed", MB_OK);
		return S_OK;
	}

	return S_OK;
}
