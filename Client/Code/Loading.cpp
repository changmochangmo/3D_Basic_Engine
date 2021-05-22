#include "stdafx.h"
#include "Loading.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"
#include "ObjectFactory.h"

#include "BoundingVolume.h"
#include "DebugCollider.h"
#include "Grid.h"
#include "Player.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextManager.h"

#include "BossScene.h"

CLoading::CLoading()
{
}


CLoading::~CLoading()
{
}

_uint CLoading::ThreadMain(void * pArg)
{
	CLoading* pLoading = (CLoading*)pArg;

	_uint iFlag = 0;

	EnterCriticalSection(&pLoading->m_crt);

	switch (pLoading->GetLoadingID())
	{
	case (_int)ELoadingID::StaticResource:
		
		break;

	case (_int)ELoadingID::BossSceneResource:
		iFlag = pLoading->LoadBossScene();
		break;
	}
	
	LeaveCriticalSection(&pLoading->m_crt);
	_endthreadex(0);

	return iFlag;
}

CLoading * CLoading::Create(_int loadingID)
{
	CLoading* pInstance = new CLoading;

	pInstance->StartLoading(loadingID);
	return pInstance;
}

void CLoading::Free(void)
{
	WaitForSingleObject(m_threadHandle, INFINITE);
	CloseHandle(m_threadHandle);
	DeleteCriticalSection(&m_crt);
}

void CLoading::StartLoading(_int loadingID)
{
	InitializeCriticalSection(&m_crt);
	m_threadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadMain, this, 0, NULL);
	m_loadingID = loadingID;
}

_uint CLoading::LoadBossScene(void)
{
	m_pNextScene = CBossScene::Create();
	m_pNextScene->Start();

	m_finish = true;
	
	return 0;
}