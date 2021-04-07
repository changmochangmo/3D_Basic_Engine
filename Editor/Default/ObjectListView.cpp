// ObjectListView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "ObjectListView.h"
#include "EditorView.h"
#include "MainFrm.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "DeviceManager.h"
#include "EditorScene.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CObjectListView

IMPLEMENT_DYNCREATE(CObjectListView, CFormView)

CObjectListView::CObjectListView()
	: CFormView(IDD_OBJECTLISTVIEW)
{
	
}

CObjectListView::~CObjectListView()
{
}

void CObjectListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

BEGIN_MESSAGE_MAP(CObjectListView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectListView::OnBnClickedUP)
	ON_BN_CLICKED(IDC_BUTTON2, &CObjectListView::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_BUTTON3, &CObjectListView::OnBnClickedRight)
	ON_BN_CLICKED(IDC_BUTTON4, &CObjectListView::OnBnClickedDown)
	ON_BN_CLICKED(IDC_BUTTON6, &CObjectListView::OnBnClickedForward)
	ON_BN_CLICKED(IDC_BUTTON5, &CObjectListView::OnBnClickedBack)
	ON_BN_CLICKED(IDC_BUTTON7, &CObjectListView::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CObjectListView::OnBnClickedLoad)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectListView::OnLbnSelchangeObjectList)
	ON_BN_CLICKED(IDC_RADIO1, &CObjectListView::OnBnClickedWhite)
	ON_BN_CLICKED(IDC_RADIO2, &CObjectListView::OnBnClickedRed)
	ON_BN_CLICKED(IDC_RADIO3, &CObjectListView::OnBnClickedBlue)
	ON_BN_CLICKED(IDC_RADIO4, &CObjectListView::OnBnClickedGreen)
	ON_BN_CLICKED(IDC_RADIO5, &CObjectListView::OnBnClickedYellow)
END_MESSAGE_MAP()


// CObjectListView 진단입니다.

#ifdef _DEBUG
void CObjectListView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjectListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjectListView 메시지 처리기입니다.


void CObjectListView::OnBnClickedUP()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	pView->TopSpawnObject();
}


void CObjectListView::OnBnClickedLeft()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	pView->LeftSpawnObject();
}


void CObjectListView::OnBnClickedRight()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	pView->RightSpawnObject();
}


void CObjectListView::OnBnClickedDown()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	pView->BottomSpawnObject();
}


void CObjectListView::OnBnClickedForward()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	pView->ForwardSpawnObject();
}


void CObjectListView::OnBnClickedBack()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));
	pView->BackSpawnObject();
}


void CObjectListView::OnBnClickedSave()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));

	std::string filePath = "../../Data/Save_2.txt";
	std::wofstream ofsSave(filePath.data());

	if (ofsSave.is_open())
	{
		for (auto& pObj : pView->GetGameObjects())
		{
			ofsSave << "m_objectKey=" << pObj->GetObjectKey() << "\n";
			ofsSave << pObj->GetComponent<Engine::CTransformC>()->GetPosition().x << "\n";
			ofsSave << pObj->GetComponent<Engine::CTransformC>()->GetPosition().y << "\n";
			ofsSave << pObj->GetComponent<Engine::CTransformC>()->GetPosition().z << "\n";
			ofsSave << pObj->GetComponent<Engine::CTransformC>()->GetRotation().x << "\n";
			ofsSave << pObj->GetComponent<Engine::CTransformC>()->GetRotation().y << "\n";
			ofsSave << pObj->GetComponent<Engine::CTransformC>()->GetRotation().z << "\n";

		}

		AfxMessageBox(L"Save Success | ObjectListView.cpp");
	}
	else AfxMessageBox(L"Save Failed | ObjectListView.cpp");
}


void CObjectListView::OnBnClickedLoad()
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));

	if (!pView->GetGameObjects().empty())
	{
		pView->Release_CubeData();
	}

	std::string filePath = "../../Data/Save_3.txt";
	std::ifstream ifsLoad(filePath.data());

	if (ifsLoad.is_open())
	{
		std::string line;

		while (!ifsLoad.eof())
		{
			std::string ObjectKey;

			if (std::getline(ifsLoad, line))
				ObjectKey = line;
			else
				break;

			float xPos = 0.f, yPos = 0.f, zPos = 0.f;
			float xRot = 0.f, yRot = 0.f, zRot = 0.f;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr(line);
				ssr >> xPos;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr2(line);
				ssr2 >> yPos;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr3(line);
				ssr3 >> zPos;
			}
			else
				break;
			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr4(line);
				ssr4 >> xRot;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr5(line);
				ssr5 >> yRot;
			}
			else
				break;

			if (std::getline(ifsLoad, line))
			{
				std::stringstream ssr6(line);
				ssr6 >> zRot;
			}
			else
				break;
		

			SP(Engine::CGameObject) pObj = nullptr;

			if (ObjectKey == "m_objectKey=WhiteBlock")
			{
			    pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock");
				pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(xPos,
					yPos,
					zPos));
				pObj->GetComponent<Engine::CTransformC>()->SetRotation(_float3(xRot,
					yRot,
					zRot));
			}
			else if (ObjectKey == "m_objectKey=RedBlock")
			{
				pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RedBlock");
				pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(xPos,
					yPos,
					zPos));
				pObj->GetComponent<Engine::CTransformC>()->SetRotation(_float3(xRot,
					yRot,
					zRot));
			}
			else if (ObjectKey == "m_objectKey=BlueBlock")
			{
				pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"BlueBlock");
				pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(xPos,
					yPos,
					zPos));
				pObj->GetComponent<Engine::CTransformC>()->SetRotation(_float3(xRot,
					yRot,
					zRot));
			}
			else if (ObjectKey == "m_objectKey=YellowBlock")
			{
				pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"YellowBlock");
				pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(xPos,
					yPos,
					zPos));
				pObj->GetComponent<Engine::CTransformC>()->SetRotation(_float3(xRot,
					yRot,
					zRot));
			}
			else if (ObjectKey == "m_objectKey=GreenBlock")
			{
				pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"GreenBlock");
				pObj->GetComponent<Engine::CTransformC>()->SetPosition(_float3(xPos,
					yPos,
					zPos));
				pObj->GetComponent<Engine::CTransformC>()->SetRotation(_float3(xRot,
					yRot,
					zRot));
			}



			pView->Set_CubeData(pObj);
			pView->Set_CubePos(pObj->GetComponent<Engine::CTransformC>()->GetPosition());
			m_ListBox.AddString(pObj->GetObjectKey().c_str());
		}
		pView->GetGameObjects().reserve(5000);
		AfxMessageBox(L"Load Success | ObjectListView.cpp");
	}
	else
	{
		AfxMessageBox(L"Load Failed | ObjectListView.cpp");
	}
}

void CObjectListView::OnLbnSelchangeObjectList()
{
	UpdateData(TRUE);
	int Idx = m_ListBox.GetCurSel() - 1;
	++m_iCnt;

	if (m_iCnt > 0)
	{

		if (LB_ERR == Idx)
			return;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CEditorView* pView = dynamic_cast<CEditorView*>(pMain->m_mainSplitter.GetPane(0, 0));

		if (pView->GetGameObjects()[Idx ].get() == nullptr || pView->GetGameObjects()[m_iSelect].get() == nullptr)
			return;

		Engine::GET_CUR_SCENE->GetMainCamera()->GetTransform()->SetPosition(_float3(
			pView->GetGameObjects()[Idx]->GetComponent<Engine::CTransformC>()->GetPosition().x,
			pView->GetGameObjects()[Idx]->GetComponent<Engine::CTransformC>()->GetPosition().y,
			Engine::GET_CUR_SCENE->GetMainCamera()->GetTransform()->GetPosition().z));		

		if (m_iSelect != Idx)
		{
		    pView->GetGameObjects()[Idx]->GetComponent<Engine::CGraphicsC>()->SetRenderID(Engine::ERenderID::WireFrame);
			pView->GetGameObjects()[m_iSelect]->GetComponent<Engine::CGraphicsC>()->SetRenderID(Engine::ERenderID::Base);
		}

		Engine::GET_CUR_SCENE->GetMainCamera()->GetTransform()->SetRotation(_float3(0.f, 0.f, 0.f));
		
		m_iSelect = Idx;

		m_iCnt = 0;

		pView->m_curSelectedObject = pView->GetGameObjects()[Idx]; // 현재 선택한 오브젝트를 저장

		std::cout << "rotation X: " << pView->GetGameObjects()[Idx]->GetComponent<Engine::CTransformC>()->GetRotation().x << std::endl;
		std::cout << "rotation Y: " << pView->GetGameObjects()[Idx]->GetComponent<Engine::CTransformC>()->GetRotation().y << std::endl;
		std::cout << "rotation Z: " << pView->GetGameObjects()[Idx]->GetComponent<Engine::CTransformC>()->GetRotation().z << std::endl;
		std::cout << "//////////////////////////////////" << std::endl;
	}

	UpdateData(FALSE);
}

void CObjectListView::OnBnClickedWhite()
{
	m_wsBlockColor = L"WhiteBlock";
}

void CObjectListView::OnBnClickedRed()
{
	m_wsBlockColor = L"RedBlock";
}

void CObjectListView::OnBnClickedBlue()
{
	m_wsBlockColor = L"BlueBlock";
}

void CObjectListView::OnBnClickedGreen()
{
	m_wsBlockColor = L"GreenBlock";
}

void CObjectListView::OnBnClickedYellow()
{
	m_wsBlockColor = L"YellowBlock";
}
