#pragma once
#include "afxwin.h"

// CShaderView �� ���Դϴ�.

class CShaderView : public CFormView
{
	DECLARE_DYNCREATE(CShaderView)

protected:
	CShaderView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCoord();
	afx_msg void OnBnClickedButtonRotation();
	afx_msg void OnBnClickedButtonSize();
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
	CEdit m_sizeX;
	CEdit m_sizeY;
	CEdit m_sizeZ;
	CEdit m_faceBeginX;
	CEdit m_faceBeginY;
	CEdit m_faceBeginZ;
	CEdit m_beginToEndForFace;

private:
	SP(Engine::CObject) m_pBeginCubeForFace; // �� ������ ���� ť��
	std::vector<SP(Engine::CObject)> m_vFaceObjects; // ������ ������ �鿡 ���ԵǴ� ť���
	SP(Engine::CObject) m_pNormOfFaceObject; // �� ������ �����̵Ǿ��� ť��
};


