#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CInifileTab 대화 상자입니다.
class CMeshTab;
class CIniMeshTab;
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
