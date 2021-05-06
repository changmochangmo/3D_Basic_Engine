#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CInifileTab ��ȭ �����Դϴ�.
class CMeshTab;
class CIniMeshTab;
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
	void SetupScreen(void);

	CMeshTab*	m_pMeshTab = nullptr;
public:
	CButton		m_generate;
	
	CString		m_objectKey;
	CString		m_sectionKey;
	CString		m_sceneName;
	

	_int		m_numOfMesh;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();

	CTabCtrl m_tabCtrl;

	CIniMeshTab*	m_pIniMeshTab;
	int m_renderID;
};
