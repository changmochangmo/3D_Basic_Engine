#pragma once
#include "Scene.h"

class CEditorScene final : public Engine::CScene
{
	SMART_DELETER_REGISTER
public:
	explicit CEditorScene();
	~CEditorScene();

public:
	static			SHARED(Engine::CScene)	Create(void);

	virtual void Awake(void) override;
	virtual void Start(void) override;
	virtual _uint FixedUpdate(void) override;
	virtual _uint Update(void) override;
	virtual _uint LateUpdate(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;
	virtual void InitLayers(void) override;
	virtual void InitPrototypes(void) override;
	

private:
	void BlockPicking();
	void SetAddFirstCubeToListBox(); // ó�� ��ġ�Ǿ� �ִ� ť�긦 ListBox�� �߰�. ù update �� �� ���� ������
	void ChangeCameraYaxis(); // z,xŰ�� ������ ī�޶� y�� ���� z�� ����, x�� �Ʒ���.
	void CreateCubeWhenClicked();
	void DeleteCubeWhenClicked();
	void SelectBlock(); // ��ŷ ��尡 �ƴ� �� ť�긦 �����ϰ� ��

private:
	_bool m_isPickingMode = false;
	_bool m_AddFistCubeToListBox = true;
	class Engine::CGameObject* m_pPreSelectedObject = nullptr;
	class Engine::CGameObject* m_pCurSelectedObject = nullptr;

	class CMainFrame * m_pMain;
	class CEditorView* m_pEditorView;
	class CObjectListView* m_pListView;
};

