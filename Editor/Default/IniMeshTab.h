#pragma once
#include "afxcmn.h"


// CIniMeshTab 대화 상자입니다.
class CIniMeshInfoTab;
class CIniMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CIniMeshTab)

public:
	CIniMeshTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIniMeshTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIMESHTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	_int m_tabIndex = 0;
	_int m_aniIndex = 0;
public:
	void AddTab(CString meshName);
	void ClearTab(void);
	_bool SetAniIndices(void);
public:
	CTabCtrl m_tabCtrl;

	std::vector<CIniMeshInfoTab*> m_vIniMeshInfoTabs;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
