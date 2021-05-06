#pragma once
#include "afxwin.h"


// CEmptyObjectTab 대화 상자입니다.
class CMeshTab;
class CObjectsTab;
class CEmptyObjectTab : public CDialogEx
{
	DECLARE_DYNAMIC(CEmptyObjectTab)

public:
	CEmptyObjectTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEmptyObjectTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMPTYOBJECTTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
