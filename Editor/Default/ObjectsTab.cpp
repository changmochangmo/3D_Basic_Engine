// ObjectsTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "ObjectsTab.h"
#include "afxdialogex.h"


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
	DDX_Control(pDX, IDC_LIST1, m_texList);
	DDX_Control(pDX, IDC_EDIT2, m_meshKey);
}


BEGIN_MESSAGE_MAP(CObjectsTab, CDialogEx)
END_MESSAGE_MAP()


// CObjectsTab 메시지 처리기입니다.
