// MenuView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "MenuView.h"
#include "ObjectListView.h"

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
}

BEGIN_MESSAGE_MAP(CMenuView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMenuView::OpenObjectTab)
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


void CMenuView::OpenObjectTab()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_objectListView.ShowWindow(SW_SHOW);
}


void CMenuView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	if (m_objectListView.GetSafeHwnd() == nullptr)
		m_objectListView.Create(IDD_OBJECTLISTVIEW);
}
