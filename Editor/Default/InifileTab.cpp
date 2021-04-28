// ObjectsTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "InifileTab.h"
#include "afxdialogex.h"


// CInifileTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInifileTab, CDialogEx)

CInifileTab::CInifileTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INIFILETAB, pParent)
	, m_objectKey(_T(""))
	, m_sectionKey(_T(""))
	, m_sceneName(_T(""))
	, m_meshKey(_T(""))
	, m_renderID(_T(""))
{

}

CInifileTab::~CInifileTab()
{
}

void CInifileTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_texList);
	DDX_Control(pDX, IDC_BUTTON1, m_generate);
	DDX_Text(pDX, IDC_EDIT4, m_objectKey);
	DDX_Text(pDX, IDC_EDIT1, m_sectionKey);
	DDX_Text(pDX, IDC_EDIT5, m_sceneName);
	DDX_Text(pDX, IDC_EDIT2, m_meshKey);
	DDX_Control(pDX, IDC_CHECK1, m_isStatic);
	DDX_Control(pDX, IDC_CHECK3, m_needDebug);
	DDX_Text(pDX, IDC_EDIT3, m_renderID);
}

void CInifileTab::Update(void)
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CInifileTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInifileTab::OnBnClickedButton1)
END_MESSAGE_MAP()


// CInifileTab 메시지 처리기입니다.




BOOL CInifileTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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

	ofs << L"//MeshComponent\n";
	ofs << L"meshKey=" << m_meshKey << L'\n' << L'\n';

	ofs << L"//TextureComponent\n";
	ofs << L"numOfTex=" << m_texList.GetCount() << L'\n';

	for (_int i = 0; i < m_texList.GetCount(); ++i)
	{
		CString texKey;
		m_texList.GetText(i, texKey);
		ofs << L"textureKey" << i << L"=" << std::wstring(texKey) << '\n' << L'n';
	}


	ofs << L"\n//GraphicsComponent\n";
	ofs << L"renderID=" << m_renderID << L'\n' << L'\n';


	if (m_needDebug)
		ofs << L"debugMeshKey=Cube\n";

	ofs.close();
	UpdateData(FALSE);
}
