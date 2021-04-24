#include "stdafx.h"
#include "MainEditor.h"
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "ShaderManager.h"
#include "EditorScene.h"
#include "TextManager.h"

CMainEditor::CMainEditor()
{
}


CMainEditor::~CMainEditor()
{
	OnDestroy();
}

SP(CMainEditor) CMainEditor::Create(void)
{
	SP(CMainEditor) pMainEditor(new CMainEditor, Engine::SmartDeleter<CMainEditor>);

	return pMainEditor;
}

void CMainEditor::Awake(void)
{
	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CTextManager::GetInstance()->Awake();
}

void CMainEditor::Start(void)
{
	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CEditorScene::Create());
	Engine::CShaderManager::GetInstance()->Start();
	Engine::CTextManager::GetInstance()->Start();

}

void CMainEditor::FixedUpdate(void)
{
	Engine::CGraphicsManager::GetInstance()->FixedUpdate();
	Engine::CInputManager::GetInstance()->FixedUpdate();
	Engine::CSceneManager::GetInstance()->FixedUpdate();
}

void CMainEditor::Update(void)
{
	Engine::CGraphicsManager::GetInstance()->Update();
	Engine::CInputManager::GetInstance()->Update();
	Engine::CSceneManager::GetInstance()->Update();
}

void CMainEditor::LateUpdate(void)
{
	Engine::CGraphicsManager::GetInstance()->LateUpdate();
	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();
}

void CMainEditor::PreRender(void)
{
	Engine::CGraphicsManager::GetInstance()->PreRender();
}

void CMainEditor::Render(void)
{
	Engine::CGraphicsManager::GetInstance()->Render();
	Engine::CTextManager::GetInstance()->Render();
}

void CMainEditor::PostRender(void)
{
	Engine::CGraphicsManager::GetInstance()->PostRender();
}

void CMainEditor::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CObjectFactory::GetInstance()->DestroyInstance();
	Engine::CShaderManager::GetInstance()->DestroyInstance();	
}

void CMainEditor::OnEnable(void)
{
}

void CMainEditor::OnDisable(void)
{
}
