#pragma once
#include "afxwin.h"


// CTextureTab 대화 상자입니다.

class CTextureTab : public CDialogEx
{
	DECLARE_DYNAMIC(CTextureTab)

public:
	CTextureTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTextureTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTURETAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void Update(void);

	CListBox m_texList;
};
