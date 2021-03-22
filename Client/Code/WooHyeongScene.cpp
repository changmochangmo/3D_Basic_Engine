#include "stdafx.h"
#include "WoohyeongScene.h"


CWoohyeongScene::CWoohyeongScene()
{
}


CWoohyeongScene::~CWoohyeongScene()
{
}

SHARED(Engine::CScene) CWoohyeongScene::Create(void)
{
	SHARED(CWoohyeongScene) pCLogoScene(new CWoohyeongScene, Engine::SmartDeleter<CWoohyeongScene>);

	return pCLogoScene;
}

void CWoohyeongScene::Awake(void)
{
	/*{
	SHARED(Engine::CGameObject) obj = Engine::CGameObject::Create(L"LayerKey", L"ObjectKey");
	obj->AddComponent<Engine::CMeshComponent>();
	obj->AddComponent<Engine::CAabbColliderComponent>()->SetPosition(_float3(150, 150, 0));

	Engine::CObjectManager::GetInstance()->AddPrototype(obj, (_uint)ESceneType::Static);
	}*/

	//{
	//	m_name = GetCurClassName(this);
	//	SetWindowText(Engine::GET_HANDLE, m_name.c_str());

	//	m_mLayers[L"Default"] = Engine::CLayer::Create(L"Default");
	//	m_mLayers[L"Player"] = Engine::CLayer::Create(L"Player");

	//	SHARED(Engine::CGameObject) obj = Engine::CGameObject::Create(L"Default", L"Default");
	//	Engine::CObjectFactory::GetInstance()->AddPrototype(obj);

	//	obj = Engine::CGameObject::Create(L"Player", L"Player");
	//	obj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"cube");
	//	obj->AddComponent<Engine::CTextureComponent>()->SetLayerKey(L"StaticScene");
	//	obj->AddComponent<Engine::CTransformComponent>();
	//	obj->AddComponent<Engine::CGraphicsComponent>();
	//	obj->AddColliderToManager<Engine::CAabbColliderComponent>()->SetBoxSize(_float3(100, 100, 100));
	//	Engine::CObjectFactory::GetInstance()->AddPrototype(obj);
	//}
}

void CWoohyeongScene::Start(void)
{
}

_uint CWoohyeongScene::FixedUpdate(void)
{
	return _uint();
}

_uint CWoohyeongScene::Update(void)
{
	return _uint();
}

_uint CWoohyeongScene::LateUpdate(void)
{
	return _uint();
}

void CWoohyeongScene::OnDestroy(void)
{
}

void CWoohyeongScene::OnEnable(void)
{
}

void CWoohyeongScene::OnDisable(void)
{
}

void CWoohyeongScene::InitLayers(void)
{
}

void CWoohyeongScene::InitPrototypes(void)
{
}
