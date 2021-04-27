// ObjectsTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "ObjectsTab.h"
#include "afxdialogex.h"
#include "ObjectFactory.h"
#include "Object.h"

// CObjectsTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectsTab, CDialogEx)

CObjectsTab::CObjectsTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OBJECTSTAB, pParent)
{

}

CObjectsTab::~CObjectsTab()
{
}

void CObjectsTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_objectList);
	DDX_Control(pDX, IDC_LIST3, m_scenePrototypeList);
	DDX_Control(pDX, IDC_LIST1, m_staticPrototypeList);
}


BEGIN_MESSAGE_MAP(CObjectsTab, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectsTab::StaticPrototypeListSelChange)
	ON_LBN_SELCHANGE(IDC_LIST3, &CObjectsTab::ScenePrototypeListSelChange)
END_MESSAGE_MAP()


// CObjectsTab 메시지 처리기입니다.


BOOL CObjectsTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	for (auto& prototype : Engine::CObjectFactory::GetInstance()->GetCurPrototypes())
		m_scenePrototypeList.AddString(prototype.first.c_str());
	for (auto& prototype : Engine::CObjectFactory::GetInstance()->GetStaticPrototypes())
		m_staticPrototypeList.AddString(prototype.first.c_str());

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CObjectsTab::StaticPrototypeListSelChange()
{
	UpdateData(TRUE);
	m_staticPrototypeIndex = m_staticPrototypeList.GetCurSel();
	CString prototypeKey;
	m_staticPrototypeList.GetText(m_staticPrototypeIndex, prototypeKey);
	
	m_scenePrototypeList.SetSel(m_scenePrototypeIndex, FALSE);
	m_scenePrototypeIndex = UNDEFINED;
	

	m_selectedObjKey	= prototypeKey;
	m_selectedIsStatic	= true;


	UpdateData(FALSE);
}


void CObjectsTab::ScenePrototypeListSelChange()
{
	UpdateData(TRUE);
	m_scenePrototypeIndex = m_scenePrototypeList.GetCurSel();
	CString prototypeKey;
	m_scenePrototypeList.GetText(m_scenePrototypeIndex, prototypeKey);

	m_staticPrototypeList.SetSel(m_staticPrototypeIndex, FALSE);
	m_staticPrototypeIndex = UNDEFINED;


	m_selectedObjKey = prototypeKey;
	m_selectedIsStatic = false;


	UpdateData(FALSE);
}
