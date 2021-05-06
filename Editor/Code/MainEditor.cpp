#include "stdafx.h"
#include "MainEditor.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "TextManager.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "FRC.h"

#pragma region IncludeScenes
#include "EditorScene.h"
#pragma endregion

#pragma region Prototypes
#include "Player.h"
#include "Grid.h"
#include "EmptyObject.h"
#pragma endregion

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
	srand((_uint)time(NULL));

	Engine::CTextManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSoundManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CCameraManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CCollisionManager::GetInstance()->Awake();
}

void CMainEditor::Start(void)
{
	InitStaticPrototype();

	Engine::CTextManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CEditorScene::Create());
	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CCameraManager::GetInstance()->Start();
	Engine::CShaderManager::GetInstance()->Start();

	Engine::CCollisionManager::GetInstance()->Start((_int)EColliderID::NumOfColliderID);
}

void CMainEditor::FixedUpdate(void)
{
	Engine::CSceneManager::GetInstance()->FixedUpdate();
	Engine::CInputManager::GetInstance()->FixedUpdate();
	Engine::CGraphicsManager::GetInstance()->FixedUpdate();
}

void CMainEditor::Update(void)
{
	Engine::CInputManager::GetInstance()->Update();
	Engine::CSceneManager::GetInstance()->Update();

	Engine::CCameraManager::GetInstance()->Update();
	Engine::CCollisionManager::GetInstance()->Update();
	Engine::CGraphicsManager::GetInstance()->Update();
}

void CMainEditor::LateUpdate(void)
{
	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();

	Engine::CCameraManager::GetInstance()->LateUpdate();
	Engine::CCollisionManager::GetInstance()->LateUpdate();
	Engine::CGraphicsManager::GetInstance()->LateUpdate();
}

void CMainEditor::PreRender(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->PreRender();
	Engine::CTextManager::GetInstance()->Render();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainEditor::Render(void)
{
	Engine::CGraphicsManager::GetInstance()->Render();
	Engine::CTextManager::GetInstance()->Render();
}

void CMainEditor::PostRender(void)
{
	Engine::CGraphicsManager::GetInstance()->PostRender();
	Engine::CTextManager::GetInstance()->Render();
}

void CMainEditor::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CObjectFactory::GetInstance()->DestroyInstance();
	Engine::CCollisionManager::GetInstance()->DestroyInstance();
	Engine::CSoundManager::GetInstance()->DestroyInstance();
	Engine::CCameraManager::GetInstance()->DestroyInstance();
	Engine::CShaderManager::GetInstance()->DestroyInstance();
	Engine::CTextManager::GetInstance()->DestroyInstance();
}

void CMainEditor::OnEnable(void)
{
}

void CMainEditor::OnDisable(void)
{
}

void CMainEditor::InitStaticPrototype(void)
{
	SP(Engine::CObject) spPlayerPrototype(CPlayer::Create(true));
	Engine::ADD_PROTOTYPE(spPlayerPrototype);
}
