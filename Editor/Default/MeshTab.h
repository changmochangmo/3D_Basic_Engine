#pragma once
#include "afxwin.h"


// CMeshTab 대화 상자입니다.
class CInifileTab;
class CTextureTab;
class CMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CMeshTab)

public:
	CMeshTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMeshTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESHTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CInifileTab*	m_pInifileTab = nullptr;
	CTextureTab*	m_pTexTab = nullptr;
public:
	CListBox	m_meshList;
	_uint		m_index		= 0;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList1();
};
