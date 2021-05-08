// ModifyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "ModifyDlg.h"
#include "afxdialogex.h"
#include "TransformTab.h"
#include "ObjectsTab.h"
#include "Object.h"

// CModifyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CModifyDlg, CDialogEx)

CModifyDlg::CModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODIFYDLG, pParent)
{

}

CModifyDlg::~CModifyDlg()
{
	delete m_pTransformTab;
}

void CModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

void CModifyDlg::Update(void)
{
	UpdateData(TRUE);
	m_pSelectedObject = m_pObjectsTab->m_spSelectedObject.get();
	m_pTransformTab->Update();
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CModifyDlg, CDialogEx)
END_MESSAGE_MAP()


// CModifyDlg �޽��� ó�����Դϴ�.


BOOL CModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_tabCtrl.InsertItem(0, _T("Transform"));
	m_tabCtrl.InsertItem(1, _T("Collision"));
	m_tabCtrl.InsertItem(2, _T("Graphics"));
	m_tabCtrl.SetCurSel(0);
	m_curCursel = m_tabCtrl.GetCurSel();

	CRect rc;
	m_tabCtrl.GetWindowRect(&rc);

	m_pTransformTab = new CTransformTab;
	m_pTransformTab->Create(IDD_TRANSFORMTAB, &m_tabCtrl);
	m_pTransformTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pTransformTab->ShowWindow(SW_SHOW);
	m_pTransformTab->m_pModifyDlg = this;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
