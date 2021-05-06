// ObjectsTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "InifileTab.h"
#include "afxdialogex.h"

#include "MeshTab.h"

//InifileTab's Tabs
#include "IniMeshTab.h"
#include "IniMeshInfoTab.h"

// CInifileTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInifileTab, CDialogEx)

CInifileTab::CInifileTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INIFILETAB, pParent)
	, m_objectKey(_T(""))
	, m_sectionKey(_T(""))
	, m_sceneName(_T(""))
	
	, m_renderID(0)
{

}

CInifileTab::~CInifileTab()
{
}

void CInifileTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON1, m_generate);

	DDX_Text(pDX, IDC_EDIT4, m_objectKey);
	DDX_Text(pDX, IDC_EDIT1, m_sectionKey);
	DDX_Text(pDX, IDC_EDIT5, m_sceneName);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	DDX_Text(pDX, IDC_EDIT3, m_renderID);
}

void CInifileTab::Update(void)
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CInifileTab::SetupScreen(void)
{
	UpdateData(TRUE);

	if (m_pIniMeshTab->m_vIniMeshInfoTabs.size() == 0)
	{
		_int numOfSelected = 0;
		HLOCAL selectedItems = NULL;
		LPINT rgSelected = NULL;

		numOfSelected = m_pMeshTab->m_meshList.GetSelCount();
		selectedItems = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, numOfSelected * sizeof(INT));
		rgSelected = (LPINT)LocalLock(selectedItems);
		VERIFY(m_pMeshTab->m_meshList.GetSelItems(numOfSelected, rgSelected) == numOfSelected);


		for (_int i = 0; i < numOfSelected; ++i)
		{
			CString meshKey;
			m_pMeshTab->m_meshList.GetText(rgSelected[i], meshKey);

			m_pIniMeshTab->AddTab(meshKey);
		}
	}

	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CInifileTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInifileTab::OnBnClickedButton1)
END_MESSAGE_MAP()


// CInifileTab 메시지 처리기입니다.




BOOL CInifileTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_tabCtrl.InsertItem(0, _T("Mesh"));
	m_tabCtrl.SetCurSel(0);


	CRect rc;
	m_tabCtrl.GetWindowRect(&rc);

	m_pIniMeshTab = new CIniMeshTab;
	m_pIniMeshTab->Create(IDD_INIMESHTAB, &m_tabCtrl);
	m_pIniMeshTab->MoveWindow(0, 25, rc.Width(), rc.Height());
	m_pIniMeshTab->ShowWindow(SW_SHOW);
	

	return TRUE; 
}


void CInifileTab::OnBnClickedButton1()
{
	UpdateData(TRUE);

	if (m_objectKey == "" || m_sectionKey == "" || m_sceneName == "" || m_renderID == -1)
		return;
	
	std::wstring filePath = L"../../Resource/Data/" + std::wstring(m_sceneName) + 
					   L"/" + std::wstring(m_sectionKey) + L"/" + std::wstring(m_objectKey) +
					   L".ini";
	std::wofstream ofs(filePath);
	
	std::vector<CIniMeshInfoTab*>& vIniMeshInfoTabs = m_pIniMeshTab->m_vIniMeshInfoTabs;

	ofs << L"//MeshComponent\n";
	ofs << L"numOfMeshData=" << vIniMeshInfoTabs.size() << '\n';

	for (_size i = 0; i < vIniMeshInfoTabs.size(); ++i)
	{
		std::wstring meshKey(m_pIniMeshTab->m_vIniMeshInfoTabs[i]->m_meshKey);
		ofs << L"meshKey" << i << L'=' << meshKey << L'\n';
	}
	
	ofs << L'\n';
	ofs << L"//TextureComponent\n";
	for (_size i = 0; i < vIniMeshInfoTabs.size(); ++i)
	{
		ofs << L"numOfTex_Set" << i << L'=' << vIniMeshInfoTabs[i]->m_texList.GetCount() << L'\n';
		for (_int j = 0; j < vIniMeshInfoTabs[i]->m_texList.GetCount(); ++j)
		{
			CString texName;
			vIniMeshInfoTabs[i]->m_texList.GetText(j, texName);
			std::wstring texNameString(texName);
			ofs << L"textureKey" << i << L'_' << j << L'=' << texNameString << L'\n';
		}

		ofs << L'\n';
	}
	
	
	ofs << L"\n//GraphicsComponent\n";
	ofs << L"renderID=" << m_renderID << L'\n' << L'\n';
	
	
	ofs.close();
	UpdateData(FALSE);
}
