#pragma once

#include "MainComponent.h"

class CEnemyComponent final : public Engine::CMainComponent
{
public:
	CEnemyComponent();
	virtual ~CEnemyComponent();

public:
	SHARED(Engine::CComponent)	MakeClone(Engine::CGameObject * pObject);

	void						Awake(void) override;
	void						Start(SHARED(Engine::CComponent) spThis) override;

	_uint						FixedUpdate(SHARED(Engine::CComponent) spThis) override;
	_uint						Update(SHARED(Engine::CComponent) spThis) override;
	_uint						LateUpdate(SHARED(Engine::CComponent) spThis) override;

	void						OnDestroy(void) override;
	void						OnEnable(void) override;
	void						OnDisable(void) override;

public:
	static const	EComponentID	m_s_componentID = EComponentID::Enemy;

	GETTOR_SETTOR	(SHARED(Engine::CTransformComponent),		m_pPlayerTransform,		nullptr,	PlayerTransform)
};

