// TextureTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "TextureTab.h"
#include "afxdialogex.h"


// CTextureTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTextureTab, CDialogEx)

CTextureTab::CTextureTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEXTURETAB, pParent)
{

}

CTextureTab::~CTextureTab()
{
}

void CTextureTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_texList);
}


BEGIN_MESSAGE_MAP(CTextureTab, CDialogEx)
END_MESSAGE_MAP()


// CTextureTab �޽��� ó�����Դϴ�.
