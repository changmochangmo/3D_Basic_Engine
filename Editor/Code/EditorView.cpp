
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
#include "DeviceManager.h"
#include "MenuView.h"

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


CEditorView::CEditorView()
{
}

CEditorView::~CEditorView()
{
	m_pMainEditor->OnDestroy();
	m_pMainEditor.reset();

	
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
	Engine::CWndApp::GetInstance()->SetHWnd(m_hWnd);
	Engine::CWndApp::GetInstance()->SetWndWidth(VIEWCX);
	Engine::CWndApp::GetInstance()->SetWndHeight(VIEWCY);
	Engine::CDeviceManager::GetInstance()->Start();
	Engine::CFRC::GetInstance()->Start();
	Engine::CTextureStore::GetInstance()->Start();
	Engine::CMeshStore::GetInstance()->Start();
#pragma endregion

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
	
	pMain->SetWindowPos(nullptr, 0, 0, VIEWCX + 400 + iGapX, VIEWCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	SetTimer(0, 0, nullptr);

	m_pMenuview = dynamic_cast<CMenuView*>(pMain->m_mainSplitter.GetPane(0, 1));
	
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


}



void CEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);

	_int i = 0;
	TCHAR szBuf[MAX_PATH] = L"";
	swprintf_s(szBuf, L"%d", i);

	if (Engine::CInputManager::GetInstance()->KeyDown(MOUSE_LEFT))
	{

	}
}
