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
	GETTOR(CListBox,		m_staticPrototypeList,		{},			StaticPrototypeList)
	GETTOR(CListBox,		m_scenePrototypeList,		{},			ScenePrototypeList)
	GETTOR(CListBox,		m_objectList,				{},			ObjectList)

	GETTOR(_int,			m_scenePrototypeIndex,		UNDEFINED,	ScenePrototypeIndex)
	GETTOR(_int,			m_staticPrototypeIndex,		UNDEFINED,	StaticPrototypeIndex)
	GETTOR(_int,			m_objectIndex,				UNDEFINED,	ObjectIndex)

	GETTOR(std::wstring,	m_selectedObjKey,			L"",		SelectedObjKey)

	GETTOR(_bool,			m_selectedIsStatic,			false,		SelectedIsStatic)

	virtual BOOL OnInitDialog();
	afx_msg void StaticPrototypeListSelChange();
	afx_msg void ScenePrototypeListSelChange();
};
