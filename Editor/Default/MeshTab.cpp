// MeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "MeshTab.h"
#include "TextureTab.h"
#include "afxdialogex.h"
#include "MeshStore.h"
#include "InifileTab.h"
#include "Mesh.h"

// CMeshTab 대화 상자입니다.

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


// CMeshTab 메시지 처리기입니다.


BOOL CMeshTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (auto& mesh : Engine::CMeshStore::GetInstance()->GetStaticMeshData())
	{
		m_meshList.AddString(mesh.first.c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
