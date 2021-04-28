#pragma once
#include "afxwin.h"


// CInifileTab 대화 상자입니다.

class CInifileTab : public CDialogEx
{
	DECLARE_DYNAMIC(CInifileTab)

public:
	CInifileTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInifileTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIFILETAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
