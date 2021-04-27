#pragma once
#include "afxwin.h"


// CObjectsTab 대화 상자입니다.

class CObjectsTab : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectsTab)

public:
	CObjectsTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectsTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTSTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
