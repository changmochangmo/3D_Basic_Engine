#pragma once
#include "afxwin.h"


// CObjectsTab 대화 상자입니다.

class CObjectsTab : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectsTab)

public:
	CObjectsTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectsTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTSTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_texList;
	CEdit m_meshKey;
};
