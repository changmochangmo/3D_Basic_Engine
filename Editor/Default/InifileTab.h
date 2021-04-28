#pragma once
#include "afxwin.h"


// CInifileTab ��ȭ �����Դϴ�.

class CInifileTab : public CDialogEx
{
	DECLARE_DYNAMIC(CInifileTab)

public:
	CInifileTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInifileTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIFILETAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void Update(void);
public:
	CListBox m_texList;
	CButton m_generate;
	CString m_objectKey;
	CString m_sectionKey;
	CString m_sceneName;
	CString m_meshKey;
	CString m_renderID;
	CButton m_isStatic;
	CButton m_needDebug;


	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	
	
	
	
};
