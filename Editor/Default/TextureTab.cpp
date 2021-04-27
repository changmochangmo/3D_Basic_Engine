// TextureTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "TextureTab.h"
#include "afxdialogex.h"


// CTextureTab 대화 상자입니다.

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


// CTextureTab 메시지 처리기입니다.
