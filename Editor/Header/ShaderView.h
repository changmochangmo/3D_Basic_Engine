#pragma once
#include "afxwin.h"

// CShaderView 폼 뷰입니다.

class CShaderView : public CFormView
{
	DECLARE_DYNCREATE(CShaderView)

protected:
	CShaderView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CShaderView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHADERVIEW };
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
	afx_msg void OnBnClickedButtonCoord();
	afx_msg void OnBnClickedButtonRotation();
	afx_msg void OnBnClickedButtonScale();
	afx_msg void OnBnClickedButtonFaceBegin();
	afx_msg void OnBnClickedButtonFaceEnd();
	afx_msg void OnBnClickedButtonToTheTop();
	afx_msg void OnBnClickedButtonResetForFace();

	CEdit m_coordX;
	CEdit m_coordY;
	CEdit m_coordZ;
	CEdit m_rotationX;
	CEdit m_rotationY;
	CEdit m_rotationZ;
	CEdit m_scaleX;
	CEdit m_scaleY;
	CEdit m_scaleZ;
	CEdit m_faceBeginX;
	CEdit m_faceBeginY;
	CEdit m_faceBeginZ;
	CEdit m_beginToEndForFace;

private:
	SHARED(Engine::CGameObject) m_pBeginCubeForFace; // 면 생성의 시작 큐브
	std::vector<SHARED(Engine::CGameObject)> m_vFaceObjects; // 이전에 생성한 면에 포함되는 큐브들
	SHARED(Engine::CGameObject) m_pNormOfFaceObject; // 면 생성시 기준이되었던 큐브
};


