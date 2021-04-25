#ifndef MENUVIEW_H
#define MENUVIEW_H
// CMenuView 폼 뷰입니다.

class CObjectsTab;
class CMeshTab;
class CMenuView : public CFormView
{
	DECLARE_DYNCREATE(CMenuView)

protected:
	CMenuView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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