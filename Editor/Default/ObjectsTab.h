#pragma once
#include "afxwin.h"


// CObjectsTab 대화 상자입니다.
class Engine::CObject;
class CModifyDlg;
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
	void Update(void);

	std::vector<SP(Engine::CObject)> m_vObjectList;

	SP(Engine::CObject) m_spSelectedObject;
public:
	CListBox m_scenePrototypeList;
	GETTOR(CListBox,		m_staticPrototypeList,		{},			StaticPrototypeList)
	GETTOR(CListBox,		m_objectList,				{},			ObjectList)

	GETTOR(_int,			m_scenePrototypeIndex,		UNDEFINED,	ScenePrototypeIndex)
	GETTOR(_int,			m_staticPrototypeIndex,		UNDEFINED,	StaticPrototypeIndex)
	GETTOR(_int,			m_objectIndex,				UNDEFINED,	ObjectIndex)

	GETTOR(std::wstring,	m_selectedObjKey,			L"",		SelectedObjKey)

	GETTOR(_bool,			m_selectedIsStatic,			false,		SelectedIsStatic)

	
	CButton			m_add;
	CButton			m_delete;
	CButton			m_modify;
	CButton			m_copy;

	_float			m_posX;
	_float			m_posY;
	_float			m_posZ;

	CModifyDlg*		m_pModifyDlg;

	virtual BOOL OnInitDialog();
	afx_msg void StaticPrototypeListSelChange();
	afx_msg void ScenePrototypeListSelChange();
	afx_msg void ObjectListSelChange();
	afx_msg void AddButtonClicked();
	afx_msg void DeleteButtonClicked();
	
	afx_msg void ModifyButtonClicked();
	afx_msg void CopyButtonClicked();
	afx_msg void SaveButtonClicked();
	afx_msg void LoadButtonClicked();
};
