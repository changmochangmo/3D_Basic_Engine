// ObjectsTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "ObjectsTab.h"
#include "afxdialogex.h"


// CObjectsTab ��ȭ �����Դϴ�.

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


// CObjectsTab �޽��� ó�����Դϴ�.
