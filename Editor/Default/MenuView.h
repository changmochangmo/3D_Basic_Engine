#ifndef MENUVIEW_H
#define MENUVIEW_H
// CMenuView �� ���Դϴ�.

class CObjectsTab;
class CMeshTab;
class CMenuView : public CFormView
{
	DECLARE_DYNCREATE(CMenuView)

protected:
	CMenuView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMenuView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENUVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

public:
	void HideAllTabs(void);
private:
	
public:
	virtual void OnInitialUpdate();

public:
	CTabCtrl		m_tabCtrl;

	CObjectsTab*	m_pObjectsTab;
	CMeshTab*		m_pMeshTab;

	_int			m_curCursel;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};


#endif