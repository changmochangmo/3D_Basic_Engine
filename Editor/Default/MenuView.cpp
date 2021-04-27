// MenuView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "MenuView.h"
#include "InifileTab.h"
#include "MeshTab.h"
#include "TextureTab.h"
#include "ObjectsTab.h"
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


// CMenuView �����Դϴ�.

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


// CMenuView �޽��� ó�����Դϴ�.

void CMenuView::HideAllTabs(void)
{
	m_pObjectsTab->ShowWindow(SW_HIDE);
	m_pMeshTab->ShowWindow(SW_HIDE);
	m_pTexTab->ShowWindow(SW_HIDE);
	m_pInifileTab->ShowWindow(SW_HIDE);
}

void CMenuView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_tabCtrl.InsertItem(0, _T("Objects"));
	m_tabCtrl.InsertItem(1, _T("Mesh"));
	m_tabCtrl.InsertItem(2, _T("Texture"));
	m_tabCtrl.InsertItem(3, _T("IniFile"));
	m_tabCtrl.SetCurSel(0);
	m_curCursel = m_tabCtrl.GetCurSel();


	CRect rc;
	m_tabCtrl.GetWindowRect(&rc);

	m_pObjectsTab = new CObjectsTab;
	m_pObjectsTab->Create(IDD_OBJECTSTAB, &m_tabCtrl);
	m_pObjectsTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pObjectsTab->ShowWindow(SW_SHOW);

	m_pTexTab = new CTextureTab;
	m_pTexTab->Create(IDD_MESHTAB, &m_tabCtrl);
	m_pTexTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pTexTab->ShowWindow(SW_HIDE);

	m_pInifileTab = new CInifileTab;
	m_pInifileTab->Create(IDD_INIFILETAB, &m_tabCtrl);
	m_pInifileTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pInifileTab->ShowWindow(SW_HIDE);

	m_pMeshTab = new CMeshTab;
	m_pMeshTab->Create(IDD_MESHTAB, &m_tabCtrl);
	m_pMeshTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pMeshTab->ShowWindow(SW_HIDE);
	m_pMeshTab->m_pInifileTab = m_pInifileTab;
	m_pMeshTab->m_pTexTab = m_pTexTab;
}


void CMenuView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	case 2:
		m_pTexTab->ShowWindow(SW_SHOW);
		break;

	case 3:
		m_pInifileTab->ShowWindow(SW_SHOW);
		break;

	default:
		break;
	}

	*pResult = 0;
}