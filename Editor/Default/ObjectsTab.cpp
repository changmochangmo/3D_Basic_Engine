// ObjectsTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "ObjectsTab.h"
#include "afxdialogex.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "InputManager.h"
#include "ModifyDlg.h"

// CObjectsTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectsTab, CDialogEx)

CObjectsTab::CObjectsTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OBJECTSTAB, pParent)
	, m_posX(0)
	, m_posY(0)
	, m_posZ(0)
{

}

CObjectsTab::~CObjectsTab()
{
}

void CObjectsTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_staticPrototypeList);
	DDX_Control(pDX, IDC_LIST2, m_objectList);
	DDX_Control(pDX, IDC_LIST3, m_scenePrototypeList);

	DDX_Control(pDX, IDC_BUTTON2, m_add);
	DDX_Control(pDX, IDC_BUTTON1, m_delete);

	DDX_Text(pDX, IDC_EDIT1, m_posX);
	DDX_Text(pDX, IDC_EDIT2, m_posY);
	DDX_Text(pDX, IDC_EDIT3, m_posZ);
	DDX_Control(pDX, IDC_BUTTON3, m_modify);
	DDX_Control(pDX, IDC_BUTTON4, m_copy);
}

void CObjectsTab::Update(void)
{
	UpdateData(TRUE);
	m_pModifyDlg->Update();
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CObjectsTab, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectsTab::StaticPrototypeListSelChange)
	ON_LBN_SELCHANGE(IDC_LIST3, &CObjectsTab::ScenePrototypeListSelChange)
	ON_LBN_SELCHANGE(IDC_LIST2, &CObjectsTab::ObjectListSelChange)
	ON_BN_CLICKED(IDC_BUTTON2, &CObjectsTab::AddButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectsTab::DeleteButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CObjectsTab::ModifyButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON4, &CObjectsTab::CopyButtonClicked)
END_MESSAGE_MAP()


// CObjectsTab 메시지 처리기입니다.


BOOL CObjectsTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	for (auto& prototype : Engine::CObjectFactory::GetInstance()->GetCurPrototypes())
		m_scenePrototypeList.AddString(prototype.first.c_str());
	for (auto& prototype : Engine::CObjectFactory::GetInstance()->GetStaticPrototypes())
		m_staticPrototypeList.AddString(prototype.first.c_str());


	SP(Engine::CObject) spGridClone = Engine::ADD_CLONE(L"Grid", false);
	m_objectList.AddString(spGridClone->GetName().c_str());
	m_vObjectList.emplace_back(spGridClone);

	m_pModifyDlg = new CModifyDlg;
	m_pModifyDlg->Create(IDD_MODIFYDLG, this);
	m_pModifyDlg->MoveWindow(0, 25, 380, 500);
	m_pModifyDlg->ShowWindow(SW_SHOW);
	m_pModifyDlg->m_pObjectsTab = this;
	return TRUE; 
}


void CObjectsTab::StaticPrototypeListSelChange()
{
	UpdateData(TRUE);
	m_staticPrototypeIndex = m_staticPrototypeList.GetCurSel();
	CString prototypeKey;
	m_staticPrototypeList.GetText(m_staticPrototypeIndex, prototypeKey);
	
	m_scenePrototypeList.SetCurSel(UNDEFINED);
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

	m_staticPrototypeList.SetCurSel(UNDEFINED);
	m_staticPrototypeIndex = UNDEFINED;

	m_selectedObjKey = prototypeKey;
	m_selectedIsStatic = false;


	UpdateData(FALSE);
}


void CObjectsTab::ObjectListSelChange()
{
	UpdateData(TRUE);
	m_objectIndex = m_objectList.GetCurSel();
	m_spSelectedObject = m_vObjectList[m_objectIndex];


	UpdateData(FALSE);
}

//스페이스바로 ADD 누르는거 해결좀
void CObjectsTab::AddButtonClicked()
{
	UpdateData(TRUE);

	if (m_staticPrototypeIndex == UNDEFINED && m_scenePrototypeIndex == UNDEFINED)
		return;

	SP(Engine::CObject) spClone = Engine::ADD_CLONE(m_selectedObjKey, m_selectedIsStatic);
	spClone->GetTransform()->SetPosition(_float3(m_posX, m_posY, m_posZ));

	m_objectList.AddString(spClone->GetName().c_str());
	m_vObjectList.emplace_back(spClone);

	m_spSelectedObject = spClone;
	m_objectIndex = (_int)m_vObjectList.size() - 1;
	m_objectList.SetCurSel(m_objectIndex);
	UpdateData(FALSE);
}


void CObjectsTab::DeleteButtonClicked()
{
	if (m_objectIndex == UNDEFINED)
		return;

	m_spSelectedObject->SetDeleteThis(true);
	m_spSelectedObject.reset();

	m_vObjectList.erase(m_vObjectList.begin() + m_objectIndex);

	m_objectList.DeleteString(m_objectIndex);
	m_objectList.SetCurSel(UNDEFINED);
	m_objectIndex = UNDEFINED;
}


void CObjectsTab::ModifyButtonClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//카피했을때 이름 세팅 해줘야함
void CObjectsTab::CopyButtonClicked()
{
	if (m_objectIndex == UNDEFINED)
		return;

	SP(Engine::CObject) spClone = 
		Engine::ADD_CLONE(m_spSelectedObject->GetObjectKey(), 
						  m_spSelectedObject->GetIsStatic());

	spClone->GetTransform()->CopyTransform(*m_spSelectedObject->GetTransform());

	m_objectList.AddString(spClone->GetName().c_str());
	m_vObjectList.emplace_back(spClone);

	m_spSelectedObject = spClone;
	m_objectIndex = (_int)m_vObjectList.size() - 1;
	m_objectList.SetCurSel(m_objectIndex);

}
