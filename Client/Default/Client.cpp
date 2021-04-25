// SR_BaseEngine.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"

////////// 콘솔창 띄우기/////////////
#ifdef  _DEBUG
#include <crtdbg.h>
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif //  _DEBUG
/////////////////////////////////////

#pragma region SubEngineIncludes
#include "DeviceManager.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"

#include "WndApp.h"
#include "FRC.h"
#pragma endregion

#include "MainApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#pragma region SubEnginesAwake
	Engine::CDataStore::GetInstance()->Awake();
	Engine::CDataStore::GetInstance()->InitDataMap((_uint)EDataID::NumOfDataID);
	Engine::CDataStore::GetInstance()->AddDataSection(L"BasicObject", (_uint)EDataID::BasicObject);
	Engine::CDataStore::GetInstance()->AddDataSection(L"Player", (_uint)EDataID::Player);
	Engine::CDataStore::GetInstance()->AddDataSection(L"Terrain", (_uint)EDataID::Terrain);
	Engine::CDataStore::GetInstance()->AddDataSection(L"Decoration", (_uint)EDataID::Decoration);

	Engine::CFRC::GetInstance()->Awake();
	Engine::CWndApp::GetInstance()->Awake();
	Engine::CDeviceManager::GetInstance()->Awake();
	Engine::CTextureStore::GetInstance()->Awake();
	Engine::CMeshStore::GetInstance()->Awake();
#pragma endregion

#pragma region SubEnginesStart
	Engine::CDataStore::GetInstance()->Start();
	Engine::CWndApp::GetInstance()->Start(hInstance, nCmdShow);
	Engine::CDeviceManager::GetInstance()->Start();
	Engine::CFRC::GetInstance()->Start();
	Engine::CTextureStore::GetInstance()->Start();
	Engine::CMeshStore::GetInstance()->Start();
#pragma endregion

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	SP(CMainApp) pMainApp = CMainApp::Create();
	pMainApp->Awake();
	pMainApp->Start();


	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}


		if (Engine::CFRC::GetInstance()->FrameLock())
		{
			pMainApp->FixedUpdate();
			pMainApp->Update();
			pMainApp->LateUpdate();

			pMainApp->PreRender();
			pMainApp->Render();
			pMainApp->PostRender();
		}
	}
	
	pMainApp->OnDestroy();
	pMainApp.reset();


#pragma region SubengineDestroy
	Engine::CTextureStore::GetInstance()->DestroyInstance();
	Engine::CMeshStore::GetInstance()->DestroyInstance();
	Engine::CDeviceManager::GetInstance()->DestroyInstance();
	Engine::CWndApp::GetInstance()->DestroyInstance();
	Engine::CFRC::GetInstance()->DestroyInstance();
	Engine::CDataStore::GetInstance()->DestroyInstance();
#pragma endregion
	return (int)msg.wParam;
}


