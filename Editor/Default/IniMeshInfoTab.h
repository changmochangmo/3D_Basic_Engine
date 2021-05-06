#pragma once
#include "afxwin.h"


// CIniMeshInfoTab ��ȭ �����Դϴ�.
class CIniMeshTab;
class CIniMeshInfoTab : public CDialogEx
{
	DECLARE_DYNAMIC(CIniMeshInfoTab)

public:
	CIniMeshInfoTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CIniMeshInfoTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIMESHINFOTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
