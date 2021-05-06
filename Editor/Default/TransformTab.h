#pragma once
#include "afxwin.h"


// CTransformTab 대화 상자입니다.
class CModifyDlg;
class Engine::CObject;
class CTransformTab : public CDialogEx
{
	DECLARE_DYNAMIC(CTransformTab)

public:
	CTransformTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransformTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSFORMTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void Update(void);
	
	CModifyDlg*				m_pModifyDlg;
	
public:
	float m_posX;
	float m_posY;
	float m_posZ;

	float m_sizeX;
	float m_sizeY;
	float m_sizeZ;

	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

	float m_forwardX;
	float m_forwardY;
	float m_forwardZ;

	float m_rightX;
	float m_rightY;
	float m_rightZ;

	float m_upX;
	float m_upY;
	float m_upZ;

	BOOL m_setByValue;
	BOOL m_enableRot;
	BOOL m_enableDir;

	CEdit m_xPosCtrl;
	CEdit m_yPosCtrl;
	CEdit m_zPosCtrl;

	CEdit m_xSizeCtrl;
	CEdit m_ySizeCtrl;
	CEdit m_zSizeCtrl;

	CEdit m_xRotationCtrl;
	CEdit m_yRotationCtrl;
	CEdit m_zRotationCtrl;

	CEdit m_xForwardCtrl;
	CEdit m_yForwardCtrl;
	CEdit m_zForwardCtrl;

	afx_msg void SetByValueClicked();

	
	afx_msg void ModifyButtonClicked();
	CButton m_modify;
	CButton m_rollback;
	virtual BOOL OnInitDialog();
	afx_msg void DoneButtonClicked();
	
	afx_msg void RotButtonClicked();
	afx_msg void DirButtonClicked();
	CButton m_enableRotCtrl;
	CButton m_enableDirCtrl;
};
