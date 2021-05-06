#pragma once
#include "afxwin.h"


// CIniMeshInfoTab 대화 상자입니다.
class CIniMeshTab;
class CIniMeshInfoTab : public CDialogEx
{
	DECLARE_DYNAMIC(CIniMeshInfoTab)

public:
	CIniMeshInfoTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIniMeshInfoTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIMESHINFOTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void Setup(void);

	_int m_aniIndex = -1;
	CIniMeshTab* m_pIniMeshTab;
public:
	virtual BOOL OnInitDialog();
	CString m_meshKey;
	CListBox m_texList;
	CListBox m_aniList;
	afx_msg void OnLbnSelchangeList2();
};
