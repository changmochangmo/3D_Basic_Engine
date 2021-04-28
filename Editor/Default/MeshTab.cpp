// MeshTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "MeshTab.h"
#include "TextureTab.h"
#include "afxdialogex.h"
#include "MeshStore.h"
#include "InifileTab.h"
#include "Mesh.h"

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

void CMeshTab::Update(void)
{
	UpdateData(TRUE);
	UpdateData(FALSE);
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
	
	if (m_pInifileTab != nullptr)
	{
		CString meshKey;
		m_meshList.GetText(m_index, meshKey);
		m_pInifileTab->m_meshKey = meshKey;

		Engine::CMesh* pMesh = Engine::CMeshStore::GetInstance()->GetMeshData(std::wstring(meshKey));
		m_pTexTab->m_texList.ResetContent();
		m_pInifileTab->m_texList.ResetContent();
		m_pInifileTab->UpdateData(FALSE);

		for (auto& texName : pMesh->GetTexList())
		{
			m_pInifileTab->m_texList.AddString(texName.c_str());
			m_pTexTab->m_texList.AddString(texName.c_str());
		}
	}
	UpdateData(FALSE);
}
