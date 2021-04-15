
// EditorView.h : CEditorView Ŭ������ �������̽�
//

#pragma once

#include "MainEditor.h"
#include "EditorDoc.h"
#include "Object.h"

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

private:
	_float3 m_vCurCubePos;
	_float3 m_vPreCubePos;
	_uint   m_iDirNum;
	typedef std::vector<SP(Engine::CObject)> _GAMEOBJECTS;
	GETTOR(_GAMEOBJECTS, m_vGameObjects, {}, GameObjects)
	SP(Engine::CObject) m_curSelectedObject = nullptr;

public:
	void Engine_Awake();
	void Engine_Start();	
	void ForwardSpawnObject();
	void LeftSpawnObject();
	void TopSpawnObject();
	void RightSpawnObject();
	void BottomSpawnObject();
	void BackSpawnObject();
	void Release_CubeData();
	void Delete_Block(Engine::CObject& pObj);
public:
	void Set_CubeData(SP(Engine::CObject) pObj) { m_vGameObjects.emplace_back(pObj); }
	void Set_CubePos(_float3 vPos);
	
	

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

