#pragma once
#include "afxwin.h"


// CObjectsTab ��ȭ �����Դϴ�.

class CObjectsTab : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectsTab)

public:
	CObjectsTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CObjectsTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTSTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_texList;
	CEdit m_meshKey;
};
