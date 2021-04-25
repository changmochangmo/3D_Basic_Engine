// MenuView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "MenuView.h"
#include "ObjectsTab.h"
#include "MeshTab.h"

// CMenuView

IMPLEMENT_DYNCREATE(CMenuView, CFormView)

CMenuView::CMenuView()
	: CFormView(IDD_MENUVIEW)
{

}

CMenuView::~CMenuView()
{
}

void CMenuView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CMenuView, CFormView)
	
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMenuView::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMenuView 진단입니다.

#ifdef _DEBUG
void CMenuView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMenuView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMenuView 메시지 처리기입니다.

void CMenuView::HideAllTabs(void)
{
	m_pObjectsTab->ShowWindow(SW_HIDE);
	m_pMeshTab->ShowWindow(SW_HIDE);
}

void CMenuView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//m_tabCtrl.Attach(GetDlgItem(IDC_TAB1)->m_hWnd);

	m_tabCtrl.InsertItem(0, _T("Objects"));
	m_tabCtrl.InsertItem(1, _T("Mesh"));
	m_tabCtrl.SetCurSel(0);
	m_curCursel = m_tabCtrl.GetCurSel();


	CRect rc;
	m_tabCtrl.GetWindowRect(&rc);

	m_pObjectsTab = new CObjectsTab;
	m_pObjectsTab->Create(IDD_OBJECTSTAB, &m_tabCtrl);
	m_pObjectsTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pObjectsTab->ShowWindow(SW_SHOW);

	m_pMeshTab = new CMeshTab;
	m_pMeshTab->Create(IDD_MESHTAB, &m_tabCtrl);
	m_pMeshTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pMeshTab->ShowWindow(SW_HIDE);

	m_pMeshTab->m_pObjectsTab = m_pObjectsTab;

}


void CMenuView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_curCursel = m_tabCtrl.GetCurSel();

	HideAllTabs();

	switch (m_curCursel)
	{
	case 0:
		m_pObjectsTab->ShowWindow(SW_SHOW);
		break;

	case 1:
		m_pMeshTab->ShowWindow(SW_SHOW);
		break;

	default:
		break;
	}

	*pResult = 0;
}
