
// EditorView.cpp : CEditorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Editor.h"
#endif

#include "EditorDoc.h"
#include "EditorView.h"
#include "ObjectListView.h"
#include "DeviceManager.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"

#include "WndApp.h"
#include "FRC.h"
#include "MainFrm.h"
#include "MainEditor.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "Layer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "CameraComponent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CEditorView



IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CEditorView 생성/소멸
HWND g_hWnd;

CEditorView::CEditorView()
{
	m_vCurCubePos = { 0.f, 0.f, 0.f };
}

CEditorView::~CEditorView()
{
	m_pMainEditor->OnDestroy();
	m_pMainEditor.reset();

	for (auto& pObj : m_vGameObjects)
	{
		pObj->OnDestroy();
		pObj.reset();
	}
	m_vGameObjects.clear();
	
	Engine::CWndApp::GetInstance()->DestroyInstance();
	Engine::CFRC::GetInstance()->DestroyInstance();
	Engine::CDataStore::GetInstance()->DestroyInstance();
	Engine::CMeshStore::GetInstance()->DestroyInstance();
	Engine::CTextureStore::GetInstance()->DestroyInstance();
	Engine::CDeviceManager::GetInstance()->DestroyInstance();
}

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.



	return CView::PreCreateWindow(cs);
}

// CEditorView 그리기

void CEditorView::OnDraw(CDC* /*pDC*/)
{
	CEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (Engine::CFRC::GetInstance()->FrameLock())
	{
		m_pMainEditor->FixedUpdate();
		m_pMainEditor->Update();
		m_pMainEditor->LateUpdate();
		
		m_pMainEditor->PreRender();
		m_pMainEditor->Render();
		m_pMainEditor->PostRender();
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CEditorView 인쇄

BOOL CEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CEditorView 진단

#ifdef _DEBUG
void CEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorDoc* CEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditorView 메시지 처리기
void CEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	g_hWnd = m_hWnd;


	Engine_Awake();
	Engine_Start();

	m_pMainEditor = CMainEditor::Create();

	m_pMainEditor->Awake();
	m_pMainEditor->Start();

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());

	RECT rcMainRect = {};
	pMain->GetWindowRect(&rcMainRect);

	::SetRect(&rcMainRect, 0, 0, rcMainRect.right - rcMainRect.left, rcMainRect.bottom - rcMainRect.top);

	RECT rcView = {};
	GetClientRect(&rcView);
	int iGapX = rcMainRect.right - rcView.right;
	int iGapY = rcMainRect.bottom - rcView.bottom;

	pMain->SetWindowPos(nullptr,//순서를 바꿔서 생성하지 않겠다. nullptr을 넣어주게 되면. 
		0, 0, 1430 + iGapX, VIEWCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	SetTimer(0, 0, nullptr);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CEditorView::Engine_Awake()
{
	Engine::CDataStore::GetInstance()->Awake();
	Engine::CWndApp::GetInstance()->Awake();
	Engine::CDeviceManager::GetInstance()->Awake();
	Engine::CMeshStore::GetInstance()->Awake();
	Engine::CTextureStore::GetInstance()->Awake();
	Engine::CFRC::GetInstance()->Awake();
}

void CEditorView::Engine_Start()
{
	Engine::CDataStore::GetInstance()->Start();
	Engine::CWndApp::GetInstance()->SetHWnd(g_hWnd);
	Engine::CWndApp::GetInstance()->SetWndWidth(VIEWCX);
	Engine::CWndApp::GetInstance()->SetWndHeight(VIEWCY);
	Engine::CDeviceManager::GetInstance()->Start();
	Engine::CMeshStore::GetInstance()->Start();
	Engine::CTextureStore::GetInstance()->Start();
	Engine::CFRC::GetInstance()->Start();
}

void CEditorView::ForwardSpawnObject()
{
	m_vPreCubePos = m_vCurCubePos;
	m_vCurCubePos.z += 1.f;

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CObjectListView* pView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(m_vCurCubePos.x,
		m_vCurCubePos.y,
		m_vCurCubePos.z));

	m_vGameObjects.emplace_back(pObj);

	pView->m_ListBox.AddString(m_vGameObjects.back()->GetObjectKey().c_str());

}

void CEditorView::LeftSpawnObject()
{
	m_vPreCubePos = m_vCurCubePos;
	m_vCurCubePos.x -= 1.f;

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CObjectListView* pView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(m_vCurCubePos.x,
		m_vCurCubePos.y,
		m_vCurCubePos.z));

	m_vGameObjects.emplace_back(pObj);	

	pView->m_ListBox.AddString(m_vGameObjects.back()->GetObjectKey().c_str());
}

void CEditorView::TopSpawnObject()
{
	m_vPreCubePos = m_vCurCubePos;
	m_vCurCubePos.y += 1.f;

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CObjectListView* pView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));


	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(m_vCurCubePos.x,
		m_vCurCubePos.y,
		m_vCurCubePos.z));
	m_vGameObjects.emplace_back(pObj);

	

	pView->m_ListBox.AddString(m_vGameObjects.back()->GetObjectKey().c_str());
}

void CEditorView::RightSpawnObject()
{
	m_vPreCubePos = m_vCurCubePos;
	m_vCurCubePos.x += 1.f;

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CObjectListView* pView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(m_vCurCubePos.x,
		m_vCurCubePos.y,
		m_vCurCubePos.z));

	m_vGameObjects.emplace_back(pObj);

	

	pView->m_ListBox.AddString(m_vGameObjects.back()->GetObjectKey().c_str());
}

void CEditorView::BottomSpawnObject()
{
	m_vPreCubePos = m_vCurCubePos;
	m_vCurCubePos.y -= 1.f;

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CObjectListView* pView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(m_vCurCubePos.x,
		m_vCurCubePos.y,
		m_vCurCubePos.z));

	m_vGameObjects.emplace_back(pObj);
	pView->m_ListBox.AddString(m_vGameObjects.back()->GetObjectKey().c_str());
}

void CEditorView::BackSpawnObject()
{
	m_vPreCubePos = m_vCurCubePos;
	m_vCurCubePos.z -= 1.f;
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CObjectListView* pView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(m_vCurCubePos.x,
		m_vCurCubePos.y,
		m_vCurCubePos.z));

	m_vGameObjects.emplace_back(pObj);

	pView->m_ListBox.AddString(m_vGameObjects.back()->GetObjectKey().c_str());
}

void CEditorView::Release_CubeData()
{
	for (auto& pObj : m_vGameObjects)
	{
		pObj->SetIsNeedToBeDeleted(true);
		pObj.reset();
	}	

	m_vGameObjects.clear();
}

void CEditorView::Delete_Block(Engine::CGameObject & pObj)
{
}

void CEditorView::Set_CubePos(_float3 vPos)
{
	m_vCurCubePos = vPos;
}


void CEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	InvalidateRect(nullptr, FALSE);
	CView::OnTimer(nIDEvent);
}


void CEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CView::OnLButtonDown(nFlags, point);

#pragma region ReturnCubeObject

	if (!m_vGameObjects.empty())
	{
		if (L"Cube" == m_vGameObjects.back()->GetLayerKey())
		{			
			// 오브젝트 삭제 구조 수정 후 고쳐야함
			m_vGameObjects.back()->SetIsEnabled(false);

			// 두번 되돌리기 했을 때 예외처리 수정해야함
			m_vCurCubePos = m_vPreCubePos;

			CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
			CObjectListView* pView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

			pView->m_ListBox.DeleteString(m_vGameObjects.size());
		}		
	}	

	if (m_vGameObjects.empty())
	{
		m_vCurCubePos = { 0.f, 0.f, 0.f };
	}

#pragma endregion

}



void CEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);

	_int i = 0;
	TCHAR szBuf[MAX_PATH] = L"";
	swprintf_s(szBuf, L"%d", i);
	//RECT rc = { 0,0,100,100 };
	//Engine::GET_DEVICE->->Get_Font()->DrawTextW(nullptr, m_szFPS, lstrlen(m_szFPS), &rc, 0, D3DCOLOR_ARGB(255, 0, 0, 0));*/
	
	if (Engine::CInputManager::GetInstance()->KeyDown(MOUSE_LEFT))
	{

	}
}
