
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "Editor.h"

#include "MainFrm.h"
#include "EditorView.h"
#include "ShaderView.h"
#include "ObjectListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect rect;
	CPoint pos;

	GetClientRect(&rect);
	pos.x = GetSystemMetrics(SM_CXSCREEN) / 2.0f - rect.Width() / 2.0f;
	pos.y = GetSystemMetrics(SM_CYSCREEN) / 2.0f - rect.Height() / 2.0f;;

	SetWindowPos(NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE);

	/*
	
	0, 0 | 0, 1
	1, 0 | 1, 1

	*/

	m_mainSplitter.CreateStatic(this, 1, 2);
	m_mainSplitter.CreateView(0, 0, RUNTIME_CLASS(CEditorView), CSize(VIEWCX, VIEWCY), pContext);

	m_uiSplitter.CreateStatic(&m_mainSplitter, 2, 1, WS_VISIBLE | WS_CHILD, m_mainSplitter.IdFromRowCol(0, 1));
	m_uiSplitter.CreateView(0, 0, RUNTIME_CLASS(CObjectListView), CSize(150, 300), pContext);
	m_uiSplitter.CreateView(1, 0, RUNTIME_CLASS(CShaderView), CSize(150, 760), pContext);

	return TRUE;
}
