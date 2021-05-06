#pragma once
#include "afxwin.h"


// CEmptyObjectTab ��ȭ �����Դϴ�.
class CMeshTab;
class CObjectsTab;
class CEmptyObjectTab : public CDialogEx
{
	DECLARE_DYNAMIC(CEmptyObjectTab)

public:
	CEmptyObjectTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEmptyObjectTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMPTYOBJECTTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void Update(void);

	CMeshTab* m_pMeshTab;
	CObjectsTab* m_pObjectsTab;
public:
	CListBox m_componentTypes;
	CListBox m_ownedComponent;
	CListBox m_meshList;
	CListBox m_texList;
	afx_msg void AddButtonClicked();
	afx_msg void DeleteButtonClicked();
	afx_msg void CopyButtonClicked();
	CEdit m_renderIDCtrl;
	int m_renderID;
	afx_msg void AddPrototypeClicked();
	virtual BOOL OnInitDialog();
	CString m_newObjKey;
	int m_layerID;
};
