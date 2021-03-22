// ShaderView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "ShaderView.h"

#include "MainFrm.h"
#include "EditorView.h"
#include "ObjectListView.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "SceneManager.h"
#include "Layer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CShaderView

IMPLEMENT_DYNCREATE(CShaderView, CFormView)

CShaderView::CShaderView()
	: CFormView(IDD_SHADERVIEW)
{

}

CShaderView::~CShaderView()
{
}

void CShaderView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_coordX);
	DDX_Control(pDX, IDC_EDIT2, m_coordY);
	DDX_Control(pDX, IDC_EDIT3, m_coordZ);
	DDX_Control(pDX, IDC_EDIT4, m_rotationX);
	DDX_Control(pDX, IDC_EDIT5, m_rotationY);
	DDX_Control(pDX, IDC_EDIT6, m_rotationZ);
	DDX_Control(pDX, IDC_EDIT7, m_scaleX);
	DDX_Control(pDX, IDC_EDIT8, m_scaleY);
	DDX_Control(pDX, IDC_EDIT9, m_scaleZ);
	DDX_Control(pDX, IDC_EDIT10, m_faceBeginX);
	DDX_Control(pDX, IDC_EDIT11, m_faceBeginY);
	DDX_Control(pDX, IDC_EDIT12, m_faceBeginZ);
	DDX_Control(pDX, IDC_EDIT13, m_beginToEndForFace);
}

BEGIN_MESSAGE_MAP(CShaderView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CShaderView::OnBnClickedButtonCoord)
	ON_BN_CLICKED(IDC_BUTTON3, &CShaderView::OnBnClickedButtonRotation)
	ON_BN_CLICKED(IDC_BUTTON4, &CShaderView::OnBnClickedButtonScale)
	ON_BN_CLICKED(IDC_BUTTON5, &CShaderView::OnBnClickedButtonFaceBegin)
	ON_BN_CLICKED(IDC_BUTTON6, &CShaderView::OnBnClickedButtonFaceEnd)
	ON_BN_CLICKED(IDC_BUTTON8, &CShaderView::OnBnClickedButtonToTheTop)
	ON_BN_CLICKED(IDC_BUTTON7, &CShaderView::OnBnClickedButtonResetForFace)
END_MESSAGE_MAP()


// CShaderView 진단입니다.

#ifdef _DEBUG
void CShaderView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShaderView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShaderView 메시지 처리기입니다.

void CShaderView::OnBnClickedButtonCoord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	if (!pEditorView->m_curSelectedObject)
		return;

	_float3 coord = { 0.f, 0.f, 0.f };
	CString str;

	m_coordX.GetWindowTextW(str);
	coord.x = (float)_wtof(str);

	m_coordY.GetWindowTextW(str);
	coord.y = (float)_wtof(str);

	m_coordZ.GetWindowTextW(str);
	coord.z = (float)_wtof(str);

	SHARED(Engine::CGameObject) target = pEditorView->m_curSelectedObject;
	auto& pTargetTC = target->GetComponent<Engine::CTransformComponent>();

	if (0.f != coord.x)
	{
		pTargetTC->SetPositionX(coord.x);
	}
	else if (0.f != coord.y)
	{
		pTargetTC->SetPositionY(coord.y);
	}
	else if (0.f != coord.z)
	{
		pTargetTC->SetPositionZ(coord.z);
	}
}

void CShaderView::OnBnClickedButtonRotation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	if (!pEditorView->m_curSelectedObject)
		return;

	_float3 rotation = { 0.f, 0.f, 0.f };
	CString str;

	m_rotationX.GetWindowTextW(str);
	rotation.x = (float)_wtof(str);

	m_rotationY.GetWindowTextW(str);
	rotation.y = (float)_wtof(str);

	m_rotationZ.GetWindowTextW(str);
	rotation.z = (float)_wtof(str);

	SHARED(Engine::CGameObject) target = pEditorView->m_curSelectedObject;
	auto& pTargetTC = target->GetComponent<Engine::CTransformComponent>();
	
	if (0.f != rotation.x)
	{
		pTargetTC->SetRotationX(D3DXToRadian(rotation.x));
	}
	else if (0.f != rotation.y)
	{
		pTargetTC->SetRotationY(D3DXToRadian(rotation.y));
	}
	else if (0.f != rotation.z)
	{
		pTargetTC->SetRotationZ(D3DXToRadian(rotation.z));
	}
}

void CShaderView::OnBnClickedButtonScale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	if (!pEditorView->m_curSelectedObject)
		return;

	_float3 scale = { 0.f, 0.f, 0.f };
	_float data = 0.f;
	CString str;

	m_scaleX.GetWindowTextW(str);
	data = (float)_wtof(str);
	if (0.f != data)
	{
		scale.x = data;
	}

	m_scaleY.GetWindowTextW(str);
	data = (float)_wtof(str);
	if (0.f != data)
	{
		scale.y = data;
	}

	m_scaleZ.GetWindowTextW(str);
	data = (float)_wtof(str);
	if (0.f != data)
	{
		scale.z = data;
	}

	SHARED(Engine::CGameObject) target = pEditorView->m_curSelectedObject;
	target->GetComponent<Engine::CTransformComponent>()->SetScale(scale);
}

void CShaderView::OnBnClickedButtonFaceBegin()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	//CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	//if (!pEditorView->m_curSelectedObject)
	//	return;

	//Engine::CGameObject* target = pEditorView->m_curSelectedObject;
	//m_pBeginCubeForFace = target;
	//_float3 coord = target->GetComponent<Engine::CTransformComponent>()->GetPosition();
	//CString str;

	//str.Format(_T("%f"), coord.x);
	//m_faceBeginX.SetWindowText(str);
	//str = "";

	//str.Format(_T("%f"), coord.y);
	//m_faceBeginY.GetWindowTextW(str);
	//str = "";

	//str.Format(_T("%f"), coord.z);
	//m_faceBeginZ.GetWindowTextW(str);
}

void CShaderView::OnBnClickedButtonFaceEnd()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	//CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	//if (!pEditorView->m_curSelectedObject)
	//	return;

	//m_pNormOfFaceObject = m_pBeginCubeForFace;
	//_float3 beginCoord = m_pBeginCubeForFace->GetComponent<Engine::CTransformComponent>()->GetPosition(); // 시작 좌표
	//_float3 coord = beginCoord;
	//std::wstring blockType = m_pBeginCubeForFace->GetLayerKey();
	//std::wstring blockColor = m_pBeginCubeForFace->GetObjectKey();

	//CString str;
	//m_beginToEndForFace.GetWindowTextW(str);
	//_uint distance = _ttoi(str); // 처음 위치 포함 x칸 떨어진 곳까지 큐브 생성

	//// 반복해서 큐브 생성하기
	//for (_uint i = 0; i < distance; ++i)
	//{
	//	for (_uint j = 0; j < distance; ++j)
	//	{
	//		if (!j)
	//		{
	//			if (!i && !j) continue;
	//			coord.z += 0.f;
	//		}
	//		else
	//		{
	//			coord.z += 1.f;
	//		}

	//		SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(blockType, blockColor, false);
	//		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(coord);

	//		pEditorView->Set_CubeData(pObj); // 모든 큐브들이 저장되는 벡터에 추가
	//		m_vFaceObjects.push_back(pObj); // 임시로 보관할 면들만 저장되는 벡터에 추가

	//		// 오브젝트 리스트에 추가
	//		std::wstring defaultCubeKey = pEditorView->GetGameObjects().back()->GetObjectKey();
	//		pListView->m_ListBox.AddString(defaultCubeKey.c_str());
	//	}
	//	coord.z = beginCoord.z;
	//	coord.x += 1.f;
	//}
}

void CShaderView::OnBnClickedButtonToTheTop()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	//CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	//m_pNormOfFaceObject = m_pBeginCubeForFace;
	//_float3 beginCoord = m_pBeginCubeForFace->GetComponent<Engine::CTransformComponent>()->GetPosition(); // 시작 좌표
	//_float3 coord = beginCoord;
	//std::wstring blockType = m_pBeginCubeForFace->GetLayerKey();
	//std::wstring blockColor = m_pBeginCubeForFace->GetObjectKey();

	//CString str;
	//m_beginToEndForFace.GetWindowTextW(str);
	//_uint distance = _ttoi(str); // 처음 위치 포함 x칸 떨어진 곳까지 큐브 생성

	//// 반복해서 큐브 생성하기
	//for (_uint i = 0; i < distance; ++i)
	//{
	//	for (_uint j = 0; j < distance; ++j)
	//	{
	//		if (!j)
	//		{
	//			if (!i && !j) continue;
	//			coord.z += 0.f;
	//		}
	//		else
	//		{
	//			coord.z += 1.f;
	//		}

	//		SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(blockType, blockColor, false);
	//		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(coord);

	//		pEditorView->Set_CubeData(pObj); // 모든 큐브들이 저장되는 벡터에 추가
	//		m_vFaceObjects.emplace_back(pObj); // 임시로 보관할 면들만 저장되는 벡터에 추가

	//		// 오브젝트 리스트에 추가
	//		std::wstring defaultCubeKey = pEditorView->GetGameObjects().back()->GetObjectKey();
	//		pListView->m_ListBox.AddString(defaultCubeKey.c_str());
	//	}
	//	coord.z = beginCoord.z;
	//	coord.y += 1.f;
	//}
}

void CShaderView::OnBnClickedButtonResetForFace()
{
	//CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	//CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	//auto& vBlocks = Engine::GET_CUR_SCENE->GetLayers()[m_pNormOfFaceObject->GetLayerKey()]->GetGameObjects();

	//for (auto& target = m_vFaceObjects.begin(); target != m_vFaceObjects.end();)
	//{
	//	// 레이어에 저장된 면에 포함된 큐브를 벡터와 리스트에서 삭제
	//	for (auto& iter = vBlocks.begin(); iter != vBlocks.end();)
	//	{
	//		if (iter->get() == target->get())
	//		{
	//			//iter->get()->OnDestroy();
	//			vBlocks.erase(iter);

	//			if (!pEditorView->GetGameObjects().empty())
	//				pEditorView->GetGameObjects().pop_back();

	//			pListView->m_ListBox.DeleteString(pEditorView->GetGameObjects().size());
	//			break;
	//		}
	//		else
	//			++iter;
	//	}
	//	target = m_vFaceObjects.erase(target);
	//}

	//m_vFaceObjects.clear();
	//m_pNormOfFaceObject = nullptr;
}