#pragma once
#include "afxcmn.h"


// CIniMeshTab ��ȭ �����Դϴ�.
class CIniMeshInfoTab;
class CIniMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CIniMeshTab)

public:
	CIniMeshTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CIniMeshTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIMESHTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
