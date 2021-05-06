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

#include "MeshData.h"
#include "DataStore.h"
#include "MapObject.h"

#include <fstream>
#include <algorithm>


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

	if (m_spSelectedObject == nullptr)
	{
		m_modify.EnableWindow(FALSE);
		m_copy.EnableWindow(FALSE);
		m_delete.EnableWindow(FALSE);
	}
	else
	{
		m_modify.EnableWindow(TRUE);
		m_copy.EnableWindow(TRUE);
		m_delete.EnableWindow(TRUE);
	}

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
	ON_BN_CLICKED(IDC_BUTTON5, &CObjectsTab::SaveButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON6, &CObjectsTab::LoadButtonClicked)
END_MESSAGE_MAP()


// CObjectsTab 메시지 처리기입니다.


BOOL CObjectsTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	for (auto& prototype : Engine::CObjectFactory::GetInstance()->GetCurPrototypes())
		m_scenePrototypeList.AddString(prototype.first.c_str());
	for (auto& prototype : Engine::CObjectFactory::GetInstance()->GetStaticPrototypes())
		m_staticPrototypeList.AddString(prototype.first.c_str());
	
	

	//Remove engine prototypes
	_int index = m_staticPrototypeList.FindString(0, L"EmptyObject");
	m_staticPrototypeList.DeleteString(index);

	index = m_staticPrototypeList.FindString(0, L"BoundingVolume");
	m_staticPrototypeList.DeleteString(index);

	index = m_staticPrototypeList.FindString(0, L"DebugCollider");
	m_staticPrototypeList.DeleteString(index);


	SP(Engine::CObject) spGridClone = Engine::ADD_CLONE(L"Grid", true);
	m_objectList.AddString(spGridClone->GetName().c_str());
	m_vObjectList.emplace_back(spGridClone);

	m_pModifyDlg = new CModifyDlg;
	m_pModifyDlg->Create(IDD_MODIFYDLG, this);
	m_pModifyDlg->MoveWindow(0, 25, 380, 500);
	m_pModifyDlg->ShowWindow(SW_HIDE);
	m_pModifyDlg->m_pObjectsTab = this;
	return TRUE; 
}


void CObjectsTab::StaticPrototypeListSelChange()
{
	UpdateData(TRUE);
	if ((m_staticPrototypeIndex = m_staticPrototypeList.GetCurSel()) == LB_ERR)
		return;

	CString prototypeKey;
	m_staticPrototypeList.GetText(m_staticPrototypeIndex, prototypeKey);
	
	m_scenePrototypeList.SetCurSel(UNDEFINED);
	m_scenePrototypeIndex = UNDEFINED;


	m_selectedObjKey	= prototypeKey;
	m_selectedIsStatic	= true;

	m_add.EnableWindow(TRUE);
	UpdateData(FALSE);
}


void CObjectsTab::ScenePrototypeListSelChange()
{
	UpdateData(TRUE);
	if ((m_scenePrototypeIndex = m_scenePrototypeList.GetCurSel()) == LB_ERR)
		return;

	CString prototypeKey;
	m_scenePrototypeList.GetText(m_scenePrototypeIndex, prototypeKey);

	m_staticPrototypeList.SetCurSel(UNDEFINED);
	m_staticPrototypeIndex = UNDEFINED;

	m_selectedObjKey = prototypeKey;
	m_selectedIsStatic = false;

	m_add.EnableWindow(TRUE);
	UpdateData(FALSE);
}


void CObjectsTab::ObjectListSelChange()
{
	UpdateData(TRUE);

	if ((m_objectIndex = m_objectList.GetCurSel()) == LB_ERR)
		return;

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

	//std::sort(m_vObjectList.begin(), m_vObjectList.end(),
	//	[](SP(Engine::CObject) first, SP(Engine::CObject) second)->_bool
	//{
	//	return first->GetName() < second->GetName();
	//});

	m_spSelectedObject = spClone;
	m_objectIndex = m_objectList.FindString(0, spClone->GetName().c_str());
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
	m_pModifyDlg->ShowWindow(SW_SHOW);
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


void CObjectsTab::SaveButtonClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::wstring filePath = L"../../Resource/Data/EditorScene/Scene/MapObjects.ini";
	std::wofstream saveFile(filePath);

	_size numOfMapObjects = m_vObjectList.size();

	saveFile << L"numOfMapObject=" << numOfMapObjects << NEW_LINE << NEW_LINE;
	for (_size i = 0; i < m_vObjectList.size(); ++i)
	{
		SP(Engine::CObject) curObj = m_vObjectList[i];
		SP(Engine::CTransformC) spTransform = curObj->GetTransform();
		SP(Engine::CMeshC) spMesh = curObj->GetComponent<Engine::CMeshC>();
		SP(Engine::CTextureC) spTex = curObj->GetComponent<Engine::CTextureC>();
		SP(Engine::CGraphicsC) spGraphics = curObj->GetComponent<Engine::CGraphicsC>();

		const std::vector<Engine::CMeshData*>& vMeshData = spMesh->GetMeshDatas();
		saveFile << i << L"_numOfMeshData=" << vMeshData.size() << NEW_LINE;
		for (_size j = 0; j < vMeshData.size(); ++j)
		{
			saveFile << i << L"_meshKey" << j << L'=' << vMeshData[j]->GetMeshKey() << NEW_LINE << NEW_LINE;

			const std::vector<std::wstring>& vTexList = vMeshData[j]->GetTexList();
			saveFile << i << L"_numOfTex_Set" << j << L'=' << vTexList.size() << NEW_LINE;
			for (_size k = 0; k < vTexList.size(); ++k)
			{
				saveFile << i << L"_texKey" << j << L'_' << k << L'=' << vTexList[k] << NEW_LINE;
			}
			saveFile << NEW_LINE;
		}
		
		saveFile << i << L"_position="	<< spTransform->GetPosition().x << L','
										<< spTransform->GetPosition().y << L','
										<< spTransform->GetPosition().z << NEW_LINE;
		saveFile << i << L"_rotation="	<< spTransform->GetRotation().x << L','
										<< spTransform->GetRotation().y << L','
										<< spTransform->GetRotation().z << NEW_LINE;
		saveFile << i << L"_size="		<< spTransform->GetSize().x		<< L','
										<< spTransform->GetSize().y		<< L','
										<< spTransform->GetSize().z		<< NEW_LINE;

		saveFile << i << L"_name=" << curObj->GetName();
		saveFile << NEW_LINE << NEW_LINE;
	}
}


void CObjectsTab::LoadButtonClicked()
{
	UpdateData(TRUE);
	_int numOfMapObject;

	for (auto& object : m_vObjectList)
		object->SetDeleteThis(true);
	m_vObjectList.clear();
	m_objectList.ResetContent();
	m_objectIndex = -1;

	Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects", L"numOfMapObject", numOfMapObject);

	for (_int i = 0; i < numOfMapObject; ++i)
	{
		SP(CMapObject) spLoadObject = 
			std::dynamic_pointer_cast<CMapObject>(Engine::ADD_CLONE(L"MapObject", false));

		m_vObjectList.emplace_back(spLoadObject);

		std::wstring name;
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
						  std::to_wstring(i) + L"_name", name);

		spLoadObject->SetName(name);
		m_objectList.AddString(name.c_str());
		
		_int numOfMeshData;
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
						  std::to_wstring(i) + L"_numOfMeshData", numOfMeshData);
		
		for (_int j = 0; j < numOfMeshData; ++j)
		{
			std::wstring meshKey;
			Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
							  std::to_wstring(i) + L"_meshKey" + std::to_wstring(j),
							  meshKey);
			spLoadObject->GetMesh()->AddMeshData(meshKey);

			const std::vector<std::wstring>& texList = spLoadObject->GetMesh()->GetMeshDatas()[j]->GetTexList();
			for (_int k = 0; k < texList.size(); ++k)
				spLoadObject->GetTexture()->AddTexture(Engine::RemoveExtension(texList[k]), j);
		}

		_float3 position, rotation, size;
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
						  std::to_wstring(i) + L"_position", position);
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
						  std::to_wstring(i) + L"_rotation", rotation);
		Engine::GET_VALUE(false, (_int)EDataID::Scene, L"MapObjects",
						  std::to_wstring(i) + L"_size", size);

		SP(Engine::CTransformC) spTransform = spLoadObject->GetTransform();
		spTransform->SetPosition(position);
		spTransform->SetRotation(rotation);
		spTransform->SetSize(size);
	}

	UpdateData(FALSE);
}
