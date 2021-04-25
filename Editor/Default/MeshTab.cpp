// MeshTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "MeshTab.h"
#include "afxdialogex.h"
#include "MeshStore.h"
#include "ObjectsTab.h"

// CMeshTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMeshTab, CDialogEx)

CMeshTab::CMeshTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MESHTAB, pParent)
{

}

CMeshTab::~CMeshTab()
{
}

void CMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_meshList);
}


BEGIN_MESSAGE_MAP(CMeshTab, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMeshTab::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CMeshTab �޽��� ó�����Դϴ�.


BOOL CMeshTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (auto& mesh : Engine::CMeshStore::GetInstance()->GetStaticMeshData())
	{
		m_meshList.AddString(mesh.first.c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMeshTab::OnLbnSelchangeList1()
{
	UpdateData(TRUE);
	m_index = m_meshList.GetCurSel();
	
	if (m_pObjectsTab != nullptr)
	{
		CString meshKey;
		m_meshList.GetText(m_index, meshKey);
		m_pObjectsTab->m_meshKey.SetWindowTextW(meshKey);		
	}
	UpdateData(FALSE);
}
