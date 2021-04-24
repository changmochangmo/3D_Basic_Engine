// ShaderView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "ShaderView.h"

#include "MainFrm.h"
#include "EditorView.h"
#include "ObjectListView.h"
#include "Object.h"
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
	DDX_Control(pDX, IDC_EDIT7, m_sizeX);
	DDX_Control(pDX, IDC_EDIT8, m_sizeY);
	DDX_Control(pDX, IDC_EDIT9, m_sizeZ);
	DDX_Control(pDX, IDC_EDIT10, m_faceBeginX);
	DDX_Control(pDX, IDC_EDIT11, m_faceBeginY);
	DDX_Control(pDX, IDC_EDIT12, m_faceBeginZ);
	DDX_Control(pDX, IDC_EDIT13, m_beginToEndForFace);
}

BEGIN_MESSAGE_MAP(CShaderView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CShaderView::OnBnClickedButtonCoord)
	ON_BN_CLICKED(IDC_BUTTON3, &CShaderView::OnBnClickedButtonRotation)
	ON_BN_CLICKED(IDC_BUTTON4, &CShaderView::OnBnClickedButtonSize)
	ON_BN_CLICKED(IDC_BUTTON5, &CShaderView::OnBnClickedButtonFaceBegin)
	ON_BN_CLICKED(IDC_BUTTON6, &CShaderView::OnBnClickedButtonFaceEnd)
	ON_BN_CLICKED(IDC_BUTTON8, &CShaderView::OnBnClickedButtonToTheTop)
	ON_BN_CLICKED(IDC_BUTTON7, &CShaderView::OnBnClickedButtonResetForFace)
END_MESSAGE_MAP()


// CShaderView �����Դϴ�.

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


// CShaderView �޽��� ó�����Դϴ�.

void CShaderView::OnBnClickedButtonCoord()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	SP(Engine::CObject) target = pEditorView->m_curSelectedObject;
	auto& pTargetTC = target->GetComponent<Engine::CTransformC>();

}

void CShaderView::OnBnClickedButtonRotation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	SP(Engine::CObject) target = pEditorView->m_curSelectedObject;
	auto& pTargetTC = target->GetComponent<Engine::CTransformC>();
	
}

void CShaderView::OnBnClickedButtonSize()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	if (!pEditorView->m_curSelectedObject)
		return;

	_float3 size = { 0.f, 0.f, 0.f };
	_float data = 0.f;
	CString str;

	m_sizeX.GetWindowTextW(str);
	data = (float)_wtof(str);
	if (0.f != data)
	{
		size.x = data;
	}

	m_sizeY.GetWindowTextW(str);
	data = (float)_wtof(str);
	if (0.f != data)
	{
		size.y = data;
	}

	m_sizeZ.GetWindowTextW(str);
	data = (float)_wtof(str);
	if (0.f != data)
	{
		size.z = data;
	}

	SP(Engine::CObject) target = pEditorView->m_curSelectedObject;
	target->GetComponent<Engine::CTransformC>()->SetSize(size);
}

void CShaderView::OnBnClickedButtonFaceBegin()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	//CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	//if (!pEditorView->m_curSelectedObject)
	//	return;

	//Engine::CObject* target = pEditorView->m_curSelectedObject;
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
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	//CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	//if (!pEditorView->m_curSelectedObject)
	//	return;

	//m_pNormOfFaceObject = m_pBeginCubeForFace;
	//_float3 beginCoord = m_pBeginCubeForFace->GetComponent<Engine::CTransformComponent>()->GetPosition(); // ���� ��ǥ
	//_float3 coord = beginCoord;
	//std::wstring blockType = m_pBeginCubeForFace->GetLayerKey();
	//std::wstring blockColor = m_pBeginCubeForFace->GetObjectKey();

	//CString str;
	//m_beginToEndForFace.GetWindowTextW(str);
	//_uint distance = _ttoi(str); // ó�� ��ġ ���� xĭ ������ ������ ť�� ����

	//// �ݺ��ؼ� ť�� �����ϱ�
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

	//		SP(Engine::CObject) pObj = Engine::ADD_CLONE(blockType, blockColor, false);
	//		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(coord);

	//		pEditorView->Set_CubeData(pObj); // ��� ť����� ����Ǵ� ���Ϳ� �߰�
	//		m_vFaceObjects.push_back(pObj); // �ӽ÷� ������ ��鸸 ����Ǵ� ���Ϳ� �߰�

	//		// ������Ʈ ����Ʈ�� �߰�
	//		std::wstring defaultCubeKey = pEditorView->GetGameObjects().back()->GetObjectKey();
	//		pListView->m_ListBox.AddString(defaultCubeKey.c_str());
	//	}
	//	coord.z = beginCoord.z;
	//	coord.x += 1.f;
	//}
}

void CShaderView::OnBnClickedButtonToTheTop()
{
	//// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CMainFrame * pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	//CObjectListView* pListView = dynamic_cast<CObjectListView*>(pMain->m_uiSplitter.GetPane(0, 0));

	//m_pNormOfFaceObject = m_pBeginCubeForFace;
	//_float3 beginCoord = m_pBeginCubeForFace->GetComponent<Engine::CTransformComponent>()->GetPosition(); // ���� ��ǥ
	//_float3 coord = beginCoord;
	//std::wstring blockType = m_pBeginCubeForFace->GetLayerKey();
	//std::wstring blockColor = m_pBeginCubeForFace->GetObjectKey();

	//CString str;
	//m_beginToEndForFace.GetWindowTextW(str);
	//_uint distance = _ttoi(str); // ó�� ��ġ ���� xĭ ������ ������ ť�� ����

	//// �ݺ��ؼ� ť�� �����ϱ�
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

	//		SP(Engine::CObject) pObj = Engine::ADD_CLONE(blockType, blockColor, false);
	//		pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(coord);

	//		pEditorView->Set_CubeData(pObj); // ��� ť����� ����Ǵ� ���Ϳ� �߰�
	//		m_vFaceObjects.emplace_back(pObj); // �ӽ÷� ������ ��鸸 ����Ǵ� ���Ϳ� �߰�

	//		// ������Ʈ ����Ʈ�� �߰�
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
	//	// ���̾ ����� �鿡 ���Ե� ť�긦 ���Ϳ� ����Ʈ���� ����
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