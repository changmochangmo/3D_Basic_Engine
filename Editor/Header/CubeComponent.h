#pragma once

#include "MainComponent.h"

class Engine::CGameObject;
class Engine::CGraphicsC;
class Engine::CTransformC;
class CCubeComponent final : public Engine::CMainComponent
{
public:
	explicit CCubeComponent();
	~CCubeComponent() = default;

public:
	SP(Engine::CComponent)	MakeClone(Engine::CGameObject * pObject);

	void						Awake(void) override;
	void						Start(SP(Engine::CComponent) spThis) override;

	_uint						FixedUpdate(SP(Engine::CComponent) spThis) override;
	_uint						Update(SP(Engine::CComponent) spThis) override;
	_uint						LateUpdate(SP(Engine::CComponent) spThis) override;

	void						OnDestroy(void) override;
	void						OnEnable(void) override;
	void						OnDisable(void) override;
private:
	void						Move(void);
protected:
	GETTOR(SP(Engine::CTransformC), m_pTransform, nullptr, Transform)
		GETTOR(SP(Engine::CGraphicsC), m_pGraphics, nullptr, Graphics)
		GETTOR_SETTOR(_float, m_moveSpeed, {}, MoveSpeed)
		GETTOR_SETTOR(_float, m_jumpForce, {}, JumpForce)

		SP(Engine::CTransformC) m_spCamTransform;

};

