
// EditorView.h : CEditorView Ŭ������ �������̽�
//

#pragma once

#include "MainEditor.h"
#include "EditorDoc.h"
#include "Object.h"

class CMenuView;
class CEditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

// Ư���Դϴ�.
public:
	CEditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	SP(CMainEditor) m_pMainEditor = nullptr;


public:
	void Engine_Awake();
	void Engine_Start();	

public:
	CMenuView*	m_pMenuview;
	

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // EditorView.cpp�� ����� ����
inline CEditorDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CEditorDoc*>(m_pDocument); }
#endif

