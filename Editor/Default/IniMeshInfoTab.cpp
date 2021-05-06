// IniMeshInfoTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "IniMeshInfoTab.h"
#include "afxdialogex.h"

#include "IniMeshTab.h"

#include "MeshStore.h"
#include "MeshData.h"


// CIniMeshInfoTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CIniMeshInfoTab, CDialogEx)

CIniMeshInfoTab::CIniMeshInfoTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INIMESHINFOTAB, pParent)
	, m_meshKey(_T(""))
{

}

CIniMeshInfoTab::~CIniMeshInfoTab()
{
}

void CIniMeshInfoTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_meshKey);
	DDX_Control(pDX, IDC_LIST1, m_texList);
	DDX_Control(pDX, IDC_LIST2, m_aniList);
}


BEGIN_MESSAGE_MAP(CIniMeshInfoTab, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST2, &CIniMeshInfoTab::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CIniMeshInfoTab 메시지 처리기입니다.


void CIniMeshInfoTab::Setup(void)
{
	Engine::CMeshData* pMeshData = Engine::CMeshStore::GetInstance()->GetMeshData(std::wstring(m_meshKey));
	for (auto& texName : pMeshData->GetTexList())
		m_texList.AddString(texName.c_str());
	for (auto& aniName : pMeshData->GetAniList())
		m_aniList.AddString(aniName.c_str());

	UpdateData(FALSE);
}

BOOL CIniMeshInfoTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CIniMeshInfoTab::OnLbnSelchangeList2()
{
	m_aniIndex = m_aniList.GetCurSel();
	m_pIniMeshTab->m_aniIndex = m_aniIndex;
	
	if (m_pIniMeshTab->SetAniIndices() == false)
	{
		m_aniList.SetCurSel(-1);
		m_aniIndex = -1;
	}
}
