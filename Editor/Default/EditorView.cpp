
// EditorView.cpp : CEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
#include "Object.h"
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CEditorView ����/�Ҹ�
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.



	return CView::PreCreateWindow(cs);
}

// CEditorView �׸���

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

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CEditorView �μ�

BOOL CEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CEditorView ����

#ifdef _DEBUG
void CEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorDoc* CEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditorView �޽��� ó����
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

	pMain->SetWindowPos(nullptr,//������ �ٲ㼭 �������� �ʰڴ�. nullptr�� �־��ְ� �Ǹ�. 
		0, 0, 1430 + iGapX, VIEWCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	SetTimer(0, 0, nullptr);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

	SP(Engine::CObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(m_vCurCubePos.x,
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

	SP(Engine::CObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(m_vCurCubePos.x,
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


	SP(Engine::CObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(m_vCurCubePos.x,
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

	SP(Engine::CObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(m_vCurCubePos.x,
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

	SP(Engine::CObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(m_vCurCubePos.x,
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

	SP(Engine::CObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(pView->m_wsBlockType, pView->m_wsBlockColor);
	pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(m_vCurCubePos.x,
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

void CEditorView::Delete_Block(Engine::CObject & pObj)
{
}

void CEditorView::Set_CubePos(_float3 vPos)
{
	m_vCurCubePos = vPos;
}


void CEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	InvalidateRect(nullptr, FALSE);
	CView::OnTimer(nIDEvent);
}


void CEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CView::OnLButtonDown(nFlags, point);

#pragma region ReturnCubeObject

	if (!m_vGameObjects.empty())
	{
		if (L"Cube" == m_vGameObjects.back()->GetLayerKey())
		{			
			// ������Ʈ ���� ���� ���� �� ���ľ���
			m_vGameObjects.back()->SetIsEnabled(false);

			// �ι� �ǵ����� ���� �� ����ó�� �����ؾ���
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
