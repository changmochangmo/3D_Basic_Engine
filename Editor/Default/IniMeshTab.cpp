// CIniMeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "IniMeshTab.h"
#include "afxdialogex.h"

#include "IniMeshInfoTab.h"


// CIniMeshTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CIniMeshTab, CDialogEx)

CIniMeshTab::CIniMeshTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INIMESHTAB, pParent)
{

}

CIniMeshTab::~CIniMeshTab()
{
}

void CIniMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

void CIniMeshTab::AddTab(CString meshName)
{
	_int numOfItem = m_tabCtrl.GetItemCount();
	m_tabCtrl.InsertItem(numOfItem, meshName);
	m_tabCtrl.SetCurSel(0);

	CRect rc;
	m_tabCtrl.GetWindowRect(&rc);
	CIniMeshInfoTab* pNewTab = new CIniMeshInfoTab;
	pNewTab->Create(IDD_INIMESHINFOTAB, &m_tabCtrl);
	pNewTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	
	pNewTab->m_pIniMeshTab = this;
	pNewTab->m_meshKey = meshName;
	pNewTab->Setup();
	m_vIniMeshInfoTabs.emplace_back(pNewTab);

	if(m_vIniMeshInfoTabs.size() == 1)
		pNewTab->ShowWindow(SW_SHOW);
	else
		pNewTab->ShowWindow(SW_HIDE);
}

void CIniMeshTab::ClearTab(void)
{
	for (auto& iniMeshInfoTab : m_vIniMeshInfoTabs)
		delete iniMeshInfoTab;
	m_vIniMeshInfoTabs.clear();
	m_tabCtrl.DeleteAllItems();
}

_bool CIniMeshTab::SetAniIndices(void)
{
	for (auto& infoTab : m_vIniMeshInfoTabs)
	{
		if (infoTab->m_aniList.GetCount() <= m_aniIndex)
			return false;
	}

	for (auto& infoTab : m_vIniMeshInfoTabs)
	{
		infoTab->m_aniIndex = m_aniIndex;
		infoTab->m_aniList.SetCurSel(m_aniIndex);
	}

	return true;
}



BEGIN_MESSAGE_MAP(CIniMeshTab, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CIniMeshTab::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CIniMeshTab 메시지 처리기입니다.


void CIniMeshTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_vIniMeshInfoTabs[m_tabIndex]->ShowWindow(SW_HIDE);
	m_tabIndex = m_tabCtrl.GetCurSel();
	m_vIniMeshInfoTabs[m_tabIndex]->ShowWindow(SW_SHOW);

	*pResult = 0;
}
