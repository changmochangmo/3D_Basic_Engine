// EmptyObjectTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "EmptyObjectTab.h"
#include "afxdialogex.h"

#include "MeshTab.h"
#include "ObjectsTab.h"

#include "ObjectFactory.h"
#include "EmptyObject.h"
#include "MeshData.h"
// CEmptyObjectTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEmptyObjectTab, CDialogEx)

CEmptyObjectTab::CEmptyObjectTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EMPTYOBJECTTAB, pParent)
	, m_renderID(0)
	, m_newObjKey(_T(""))
	, m_layerID(0)
{

}

CEmptyObjectTab::~CEmptyObjectTab()
{
}

void CEmptyObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_componentTypes);
	DDX_Control(pDX, IDC_LIST2, m_ownedComponent);
	DDX_Control(pDX, IDC_LIST3, m_meshList);
	DDX_Control(pDX, IDC_LIST4, m_texList);
	DDX_Control(pDX, IDC_EDIT1, m_renderIDCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_renderID);
	DDX_Text(pDX, IDC_EDIT2, m_newObjKey);
	DDX_Text(pDX, IDC_EDIT3, m_layerID);
}

void CEmptyObjectTab::Update(void)
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CEmptyObjectTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CEmptyObjectTab::AddButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CEmptyObjectTab::DeleteButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CEmptyObjectTab::CopyButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON4, &CEmptyObjectTab::AddPrototypeClicked)
END_MESSAGE_MAP()


// CEmptyObjectTab 메시지 처리기입니다.


void CEmptyObjectTab::AddButtonClicked()
{
	UpdateData(TRUE);

	_int numOfSelected = 0;
	HLOCAL selectedItems = NULL;
	LPINT rgSelected = NULL;

	numOfSelected = m_componentTypes.GetSelCount();
	selectedItems = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, numOfSelected * sizeof(INT));
	rgSelected = (LPINT)LocalLock(selectedItems);
	VERIFY(m_componentTypes.GetSelItems(numOfSelected, rgSelected) == numOfSelected);


	for (_int i = 0; i < numOfSelected; ++i)
	{
		_bool alreadyThere = false;
		CString addCompKey;
		m_componentTypes.GetText(rgSelected[i], addCompKey);
		m_componentTypes.SetSel(rgSelected[i], FALSE);
		for (_int j = 0; j < m_ownedComponent.GetCount(); ++j)
		{
			CString myCompKey;
			m_ownedComponent.GetText(j, myCompKey);

			if (myCompKey == addCompKey)
			{
				alreadyThere = true;
				break;
			}
		}

		if(alreadyThere == true)
			continue;

		m_ownedComponent.AddString(addCompKey);
	}

	m_componentTypes;

	UpdateData(FALSE);
}


void CEmptyObjectTab::DeleteButtonClicked()
{
	UpdateData(TRUE);

	_int numOfSelected = 0;
	HLOCAL selectedItems = NULL;
	LPINT rgSelected = NULL;

	numOfSelected = m_ownedComponent.GetSelCount();
	selectedItems = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, numOfSelected * sizeof(INT));
	rgSelected = (LPINT)LocalLock(selectedItems);
	VERIFY(m_ownedComponent.GetSelItems(numOfSelected, rgSelected) == numOfSelected);

	for (_int i = numOfSelected - 1; i >= 0; --i)
	{
		m_ownedComponent.DeleteString(rgSelected[i]);
	}

	UpdateData(FALSE);
}


void CEmptyObjectTab::CopyButtonClicked()
{
	UpdateData(TRUE);
	m_meshList.ResetContent();

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

		m_meshList.AddString(meshKey);
	}


	UpdateData(FALSE);
}


void CEmptyObjectTab::AddPrototypeClicked()
{
	UpdateData(TRUE);
	SP(Engine::CObject) spEmptyObject(Engine::CEmptyObject::Create(false));
	spEmptyObject->DeleteComponent<Engine::CTransformC>();
	spEmptyObject->SetObjectKey(std::wstring(m_newObjKey));
	spEmptyObject->SetAddExtra(true);
	spEmptyObject->SetLayerID(m_layerID);

	for (_int i = 0; i < m_ownedComponent.GetCount(); ++i)
	{
		CString curComponent;
		m_ownedComponent.GetText(i, curComponent);

		if (curComponent == "Transform")
			spEmptyObject->AddComponent<Engine::CTransformC>();
		else if (curComponent == "Mesh")
			spEmptyObject->AddComponent<Engine::CMeshC>();
		else if (curComponent == "Texture")
			spEmptyObject->AddComponent<Engine::CTextureC>();
		else if (curComponent == "Graphics")
			spEmptyObject->AddComponent<Engine::CGraphicsC>();
		else if (curComponent == "RigidBody")
			spEmptyObject->AddComponent<Engine::CRigidBodyC>();
		else if (curComponent == "Collision")
			spEmptyObject->AddComponent<Engine::CCollisionC>();
		else if (curComponent == "Camera")
			spEmptyObject->AddComponent<Engine::CCameraC>();
		else if (curComponent == "Debug")
			spEmptyObject->AddComponent<Engine::CDebugC>();
	}

	SP(Engine::CMeshC) spMesh = spEmptyObject->GetComponent<Engine::CMeshC>();
	if (spMesh != nullptr)
	{
		for (_int i = 0; i < m_meshList.GetCount(); ++i)
		{
			CString meshKey;
			m_meshList.GetText(i, meshKey);
			
			spMesh->AddMeshData(std::wstring(meshKey));
			SP(Engine::CTextureC) spTexture = 
				spEmptyObject->GetComponent<Engine::CTextureC>();

			if (spTexture != nullptr)
			{
				Engine::CMeshData* pMeshData = spMesh->GetMeshDatas()[i];

				for (auto& texKey : pMeshData->GetTexList())
				{
					spTexture->AddTexture(Engine::RemoveExtension(texKey), i);
				}
			}
		}
	}

	SP(Engine::CGraphicsC) spGraphic = spEmptyObject->GetComponent<Engine::CGraphicsC>();
	if (spGraphic != nullptr)
		spGraphic->SetRenderID(m_renderID);

	
	Engine::ADD_PROTOTYPE(spEmptyObject);
	m_pObjectsTab->m_scenePrototypeList.AddString(spEmptyObject->GetObjectKey().c_str());
	UpdateData(FALSE);
}


BOOL CEmptyObjectTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_componentTypes.AddString(L"Transform");
	m_componentTypes.AddString(L"Mesh");
	m_componentTypes.AddString(L"Texture");
	m_componentTypes.AddString(L"Graphics");

	m_componentTypes.AddString(L"RigidBody");
	m_componentTypes.AddString(L"Collision");

	m_componentTypes.AddString(L"Camera");
	m_componentTypes.AddString(L"Debug");


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
