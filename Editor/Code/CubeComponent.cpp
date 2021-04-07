#include "stdafx.h"
#include "CubeComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"

CCubeComponent::CCubeComponent()
{
}

SP(Engine::CComponent) CCubeComponent::MakeClone(Engine::CGameObject * pObject)
{
	SP(CCubeComponent) pClone(new CCubeComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	return pClone;
}

void CCubeComponent::Awake(void)
{
	__super::Awake();
	m_pOwner->SetLayerKey(L"Player");
	m_pOwner->SetObjectKey(L"Player");
}

void CCubeComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);

	m_jumpForce = 5;

	m_pTransform = m_pOwner->GetComponent<Engine::CTransformC>();
	m_pGraphics = m_pOwner->GetComponent<Engine::CGraphicsC>();
	SP(Engine::CScene) pScene = Engine::GET_CUR_SCENE;
	m_spCamTransform = Engine::GET_CUR_SCENE->GetMainCamera()->GetOwner()->GetComponent<Engine::CTransformC>();
}

_uint CCubeComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CCubeComponent::Update(SP(Engine::CComponent) spThis)
{
	return _uint();
}

_uint CCubeComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
	return _uint();
}

void CCubeComponent::OnDestroy(void)
{
}

void CCubeComponent::OnEnable(void)
{
	__super::OnEnable();
}

void CCubeComponent::OnDisable(void)
{
	__super::OnDisable();
}

void CCubeComponent::Move(void)
{
}