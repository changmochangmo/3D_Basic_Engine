#pragma once
#include "afxcmn.h"


// CModifyDlg 대화 상자입니다.
class CObjectsTab;
class CTransformTab;
class Engine::CObject;
class CModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModifyDlg)

public:
	CModifyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModifyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODIFYDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void Update(void);

	CObjectsTab*		m_pObjectsTab;
	Engine::CObject*	m_pSelectedObject;
public:
	CTabCtrl			m_tabCtrl;
	
	CTransformTab*		m_pTransformTab;

	_int				m_curCursel;
	virtual BOOL OnInitDialog();
};
