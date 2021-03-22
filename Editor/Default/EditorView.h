
// EditorView.h : CEditorView 클래스의 인터페이스
//

#pragma once

#include "MainEditor.h"
#include "EditorDoc.h"
#include "GameObject.h"

class CEditorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

// 특성입니다.
public:
	CEditorDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	SHARED(CMainEditor) m_pMainEditor = nullptr;

private:
	_float3 m_vCurCubePos;
	_float3 m_vPreCubePos;
	_uint   m_iDirNum;
	typedef std::vector<SHARED(Engine::CGameObject)> _GAMEOBJECTS;
	GETTOR(_GAMEOBJECTS, m_vGameObjects, {}, GameObjects)
	SHARED(Engine::CGameObject) m_curSelectedObject = nullptr;

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
	void Delete_Block(Engine::CGameObject& pObj);
public:
	void Set_CubeData(SHARED(Engine::CGameObject) pObj) { m_vGameObjects.emplace_back(pObj); }
	void Set_CubePos(_float3 vPos);
	
	

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // EditorView.cpp의 디버그 버전
inline CEditorDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CEditorDoc*>(m_pDocument); }
#endif

