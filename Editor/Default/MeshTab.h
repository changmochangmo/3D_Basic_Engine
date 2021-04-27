#pragma once
#include "afxwin.h"


// CMeshTab ��ȭ �����Դϴ�.
class CInifileTab;
class CTextureTab;
class CMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CMeshTab)

public:
	CMeshTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMeshTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESHTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
