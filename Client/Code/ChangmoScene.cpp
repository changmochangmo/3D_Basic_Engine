#include "stdafx.h"
#include "ChangmoScene.h"
#include "GameObject.h"
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

	SHARED(Engine::CGameObject) spPlayerClone = Engine::ADD_CLONE(L"Player", true);
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

void CChangmoScene::InitPrototypes(void)
{
}