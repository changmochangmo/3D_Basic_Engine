#pragma once
#include "afxwin.h"


// CTextureTab ��ȭ �����Դϴ�.

class CTextureTab : public CDialogEx
{
	DECLARE_DYNAMIC(CTextureTab)

public:
	CTextureTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTextureTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTURETAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void Update(void);

	CListBox m_texList;
};
