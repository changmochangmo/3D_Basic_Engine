#pragma once
#include "afxcmn.h"


// CModifyDlg ��ȭ �����Դϴ�.
class CObjectsTab;
class CTransformTab;
class Engine::CObject;
class CModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModifyDlg)

public:
	CModifyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModifyDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODIFYDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
