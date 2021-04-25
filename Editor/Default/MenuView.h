#ifndef MENUVIEW_H
#define MENUVIEW_H
// CMenuView �� ���Դϴ�.

class CObjectListView;

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
	afx_msg void OpenObjectTab();

public:
private:
	GETTOR		(CObjectListView,		m_objectListView,		nullptr,	ObjectListView)
public:
	virtual void OnInitialUpdate();
};


#endif