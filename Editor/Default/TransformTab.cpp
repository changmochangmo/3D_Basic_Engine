// TransformTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "TransformTab.h"
#include "afxdialogex.h"
#include "ModifyDlg.h"
#include "ObjectsTab.h"
#include "Object.h"

// CTransformTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTransformTab, CDialogEx)

CTransformTab::CTransformTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRANSFORMTAB, pParent)
	, m_posX(0), m_posY(0), m_posZ(0)
	, m_sizeX(0), m_sizeY(0), m_sizeZ(0)
	, m_rotationX(0), m_rotationY(0), m_rotationZ(0)
	, m_forwardX(0), m_forwardY(0), m_forwardZ(0)
	, m_rightX(0), m_rightY(0), m_rightZ(0)
	, m_upX(0), m_upY(0), m_upZ(0)
	, m_setByValue(FALSE)
	, m_enableRot(FALSE)
	, m_enableDir(FALSE)
{

}

CTransformTab::~CTransformTab()
{
}

void CTransformTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_posX);
	DDX_Text(pDX, IDC_EDIT2, m_posY);
	DDX_Text(pDX, IDC_EDIT3, m_posZ);

	DDX_Text(pDX, IDC_EDIT4, m_sizeX);
	DDX_Text(pDX, IDC_EDIT5, m_sizeY);
	DDX_Text(pDX, IDC_EDIT6, m_sizeZ);

	DDX_Text(pDX, IDC_EDIT7, m_rotationX);
	DDX_Text(pDX, IDC_EDIT8, m_rotationY);
	DDX_Text(pDX, IDC_EDIT9, m_rotationZ);

	DDX_Text(pDX, IDC_EDIT10, m_forwardX);
	DDX_Text(pDX, IDC_EDIT11, m_forwardY);
	DDX_Text(pDX, IDC_EDIT12, m_forwardZ);

	DDX_Text(pDX, IDC_EDIT13, m_rightX);
	DDX_Text(pDX, IDC_EDIT14, m_rightY);
	DDX_Text(pDX, IDC_EDIT15, m_rightZ);

	DDX_Text(pDX, IDC_EDIT16, m_upX);
	DDX_Text(pDX, IDC_EDIT17, m_upY);
	DDX_Text(pDX, IDC_EDIT18, m_upZ);

	DDX_Check(pDX, IDC_CHECK1, m_setByValue);

	DDX_Control(pDX, IDC_EDIT1, m_xPosCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_yPosCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_zPosCtrl);

	DDX_Control(pDX, IDC_EDIT4, m_xSizeCtrl);
	DDX_Control(pDX, IDC_EDIT5, m_ySizeCtrl);
	DDX_Control(pDX, IDC_EDIT6, m_zSizeCtrl);

	DDX_Control(pDX, IDC_EDIT7, m_xRotationCtrl);
	DDX_Control(pDX, IDC_EDIT8, m_yRotationCtrl);
	DDX_Control(pDX, IDC_EDIT9, m_zRotationCtrl);

	DDX_Control(pDX, IDC_EDIT10, m_xForwardCtrl);
	DDX_Control(pDX, IDC_EDIT11, m_yForwardCtrl);
	DDX_Control(pDX, IDC_EDIT12, m_zForwardCtrl);
	DDX_Control(pDX, IDC_BUTTON1, m_modify);
	DDX_Control(pDX, IDC_BUTTON3, m_rollback);

	DDX_Check(pDX, IDC_CHECK2, m_enableRot);
	DDX_Check(pDX, IDC_CHECK3, m_enableDir);
	DDX_Control(pDX, IDC_CHECK2, m_enableRotCtrl);
	DDX_Control(pDX, IDC_CHECK3, m_enableDirCtrl);
}

void CTransformTab::Update(void)
{
	Engine::CObject* pSelectedObject = m_pModifyDlg->m_pSelectedObject;
	//if (m_setByValue == TRUE)
	//{
	//	if (pSelectedObject != nullptr)
	//		m_modify.EnableWindow(TRUE);
	//	return;
	//}

	UpdateData(TRUE);
	

	if (pSelectedObject != nullptr)
	{
		Engine::CTransformC* pTransform = pSelectedObject->GetTransform().get();
		if(m_setByValue == false)
		{
			m_modify.EnableWindow(FALSE);
			
			m_posX		= pTransform->GetPosition().x;
			m_posY		= pTransform->GetPosition().y;
			m_posZ		= pTransform->GetPosition().z;

			m_sizeX		= pTransform->GetSize().x;
			m_sizeY		= pTransform->GetSize().y;
			m_sizeZ		= pTransform->GetSize().z;

		}
		else
			m_modify.EnableWindow(TRUE);
		if (m_enableRot == false)
		{
			m_rotationX = pTransform->GetRotation().x;
			m_rotationY = pTransform->GetRotation().y;
			m_rotationZ = pTransform->GetRotation().z;
		}
		if (m_enableDir == false)
		{
			m_forwardX = pTransform->GetForward().x;
			m_forwardY = pTransform->GetForward().y;
			m_forwardZ = pTransform->GetForward().z;

			m_rightX = pTransform->GetRight().x;
			m_rightY = pTransform->GetRight().y;
			m_rightZ = pTransform->GetRight().z;

			m_upX = pTransform->GetUp().x;
			m_upY = pTransform->GetUp().y;
			m_upZ = pTransform->GetUp().z;
		}
	}
	else
	{
		m_modify.EnableWindow(FALSE);
		
		m_posX		= 0;
		m_posY		= 0;
		m_posZ		= 0;
					  
		m_sizeX		= 0;
		m_sizeY		= 0;
		m_sizeZ		= 0;
					  
		m_rotationX = 0;
		m_rotationY = 0;
		m_rotationZ = 0;
					  
		m_forwardX	= 0;
		m_forwardY	= 0;
		m_forwardZ	= 0;
					  
		m_rightX	= 0;
		m_rightY	= 0;
		m_rightZ	= 0;
					  
		m_upX		= 0;
		m_upY		= 0;
		m_upZ		= 0;
	}


	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CTransformTab, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CTransformTab::SetByValueClicked)
	ON_BN_CLICKED(IDC_BUTTON1, &CTransformTab::ModifyButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CTransformTab::DoneButtonClicked)
	ON_BN_CLICKED(IDC_CHECK2, &CTransformTab::RotButtonClicked)
	ON_BN_CLICKED(IDC_CHECK3, &CTransformTab::DirButtonClicked)
END_MESSAGE_MAP()




void CTransformTab::SetByValueClicked()
{
	UpdateData(TRUE);
	if (!m_setByValue)
	{
		m_xPosCtrl.EnableWindow(FALSE);
		m_yPosCtrl.EnableWindow(FALSE);
		m_zPosCtrl.EnableWindow(FALSE);

		m_xSizeCtrl.EnableWindow(FALSE);
		m_ySizeCtrl.EnableWindow(FALSE);
		m_zSizeCtrl.EnableWindow(FALSE);

		m_xRotationCtrl.EnableWindow(FALSE);
		m_yRotationCtrl.EnableWindow(FALSE);
		m_zRotationCtrl.EnableWindow(FALSE);

		m_xForwardCtrl.EnableWindow(FALSE);
		m_yForwardCtrl.EnableWindow(FALSE);
		m_zForwardCtrl.EnableWindow(FALSE);

		m_enableRotCtrl.EnableWindow(FALSE);
		m_enableDirCtrl.EnableWindow(FALSE);
	}
	else
	{
		m_xPosCtrl.EnableWindow(TRUE);
		m_yPosCtrl.EnableWindow(TRUE);
		m_zPosCtrl.EnableWindow(TRUE);

		m_xSizeCtrl.EnableWindow(TRUE);
		m_ySizeCtrl.EnableWindow(TRUE);
		m_zSizeCtrl.EnableWindow(TRUE);

		m_enableRotCtrl.EnableWindow(TRUE);
		m_enableDirCtrl.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


void CTransformTab::ModifyButtonClicked()
{
	UpdateData(TRUE);
	Engine::CObject* pSelectedObject = m_pModifyDlg->m_pSelectedObject;
	if (pSelectedObject == nullptr)
		return;

	Engine::CTransformC* pTransform = pSelectedObject->GetTransform().get();
	pTransform->SetPosition(_float3(m_posX, m_posY, m_posZ));
	pTransform->SetSize(_float3(m_sizeX, m_sizeY, m_sizeZ));

	if(m_enableRot)
		pTransform->SetRotation(_float3(D3DXToRadian(m_rotationX), 
										D3DXToRadian(m_rotationY), 
										D3DXToRadian(m_rotationZ)));

	if(m_enableDir)
		pTransform->SetForward(_float3(m_forwardX, m_forwardY, m_forwardZ));
	UpdateData(FALSE);
}


BOOL CTransformTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_xPosCtrl.EnableWindow(FALSE);
	m_yPosCtrl.EnableWindow(FALSE);
	m_zPosCtrl.EnableWindow(FALSE);

	m_xSizeCtrl.EnableWindow(FALSE);
	m_ySizeCtrl.EnableWindow(FALSE);
	m_zSizeCtrl.EnableWindow(FALSE);

	m_xRotationCtrl.EnableWindow(FALSE);
	m_yRotationCtrl.EnableWindow(FALSE);
	m_zRotationCtrl.EnableWindow(FALSE);

	m_xForwardCtrl.EnableWindow(FALSE);
	m_yForwardCtrl.EnableWindow(FALSE);
	m_zForwardCtrl.EnableWindow(FALSE);

	m_enableRotCtrl.EnableWindow(FALSE);
	m_enableDirCtrl.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTransformTab::DoneButtonClicked()
{
	m_setByValue = FALSE;
	m_enableRot = FALSE;
	m_enableDir = FALSE;

	m_pModifyDlg->ShowWindow(SW_HIDE);


	m_xPosCtrl.EnableWindow(FALSE);
	m_yPosCtrl.EnableWindow(FALSE);
	m_zPosCtrl.EnableWindow(FALSE);

	m_xSizeCtrl.EnableWindow(FALSE);
	m_ySizeCtrl.EnableWindow(FALSE);
	m_zSizeCtrl.EnableWindow(FALSE);

	m_xRotationCtrl.EnableWindow(FALSE);
	m_yRotationCtrl.EnableWindow(FALSE);
	m_zRotationCtrl.EnableWindow(FALSE);

	m_xForwardCtrl.EnableWindow(FALSE);
	m_yForwardCtrl.EnableWindow(FALSE);
	m_zForwardCtrl.EnableWindow(FALSE);

	m_enableRotCtrl.EnableWindow(FALSE);
	m_enableDirCtrl.EnableWindow(FALSE);

	UpdateData(FALSE);
}


void CTransformTab::RotButtonClicked()
{
	UpdateData(TRUE);
	Engine::CObject* pSelectedObject = m_pModifyDlg->m_pSelectedObject;
	Engine::CTransformC* pTransform = pSelectedObject->GetTransform().get();

	if (m_enableRot)
	{
		m_enableDir = FALSE;
		m_xRotationCtrl.EnableWindow(TRUE);
		m_yRotationCtrl.EnableWindow(TRUE);
		m_zRotationCtrl.EnableWindow(TRUE);

		m_xForwardCtrl.EnableWindow(FALSE);
		m_yForwardCtrl.EnableWindow(FALSE);
		m_zForwardCtrl.EnableWindow(FALSE);

		m_forwardX = pTransform->GetForward().x;
		m_forwardY = pTransform->GetForward().y;
		m_forwardZ = pTransform->GetForward().z;

		m_rightX = pTransform->GetRight().x;
		m_rightY = pTransform->GetRight().y;
		m_rightZ = pTransform->GetRight().z;

		m_upX = pTransform->GetUp().x;
		m_upY = pTransform->GetUp().y;
		m_upZ = pTransform->GetUp().z;
	}
	else
	{
		m_xRotationCtrl.EnableWindow(FALSE);
		m_yRotationCtrl.EnableWindow(FALSE);
		m_zRotationCtrl.EnableWindow(FALSE);

		m_rotationX = pTransform->GetRotation().x;
		m_rotationY = pTransform->GetRotation().y;
		m_rotationZ = pTransform->GetRotation().z;
	}

	UpdateData(FALSE);
}


void CTransformTab::DirButtonClicked()
{
	UpdateData(TRUE);
	Engine::CObject* pSelectedObject = m_pModifyDlg->m_pSelectedObject;
	Engine::CTransformC* pTransform = pSelectedObject->GetTransform().get();

	if (m_enableDir)
	{
		m_enableRot = FALSE;
		m_xForwardCtrl.EnableWindow(TRUE);
		m_yForwardCtrl.EnableWindow(TRUE);
		m_zForwardCtrl.EnableWindow(TRUE);

		m_xRotationCtrl.EnableWindow(FALSE);
		m_yRotationCtrl.EnableWindow(FALSE);
		m_zRotationCtrl.EnableWindow(FALSE);

		m_rotationX = pTransform->GetRotation().x;
		m_rotationY = pTransform->GetRotation().y;
		m_rotationZ = pTransform->GetRotation().z;
	}
	else
	{
		m_xForwardCtrl.EnableWindow(FALSE);
		m_yForwardCtrl.EnableWindow(FALSE);
		m_zForwardCtrl.EnableWindow(FALSE);

		m_forwardX = pTransform->GetForward().x;
		m_forwardY = pTransform->GetForward().y;
		m_forwardZ = pTransform->GetForward().z;

		m_rightX = pTransform->GetRight().x;
		m_rightY = pTransform->GetRight().y;
		m_rightZ = pTransform->GetRight().z;

		m_upX = pTransform->GetUp().x;
		m_upY = pTransform->GetUp().y;
		m_upZ = pTransform->GetUp().z;
	}

	UpdateData(FALSE);
}
