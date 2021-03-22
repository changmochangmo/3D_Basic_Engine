#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H

#include "MainComponent.h"

class Engine::CGameObject;
class Engine::CGraphicsComponent;
class Engine::CTransformComponent;
class CPlayerComponent final : public Engine::CMainComponent
{
public:
	explicit	CPlayerComponent	(void);
			   ~CPlayerComponent	(void);

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

private:
	void						Move(void);
	void						PlayerMousePicking(); // �÷��̾ ���콺 �¿�Ŭ���� ���� ���� ��ȣ�ۿ��ϴ� �Լ�
	_float3						GetPlayerDir(_float3 dir);
	_bool						CheckBlocksForRayCollision(_float3 direction); // �������� ���� �浹�ϴ��� üũ. �浹�ϸ� true ��ȯ

public:
	static const	EComponentID	m_s_componentID = EComponentID::Player;

protected:
	GETTOR(SHARED(Engine::CTransformComponent), m_pTransform, nullptr, Transform)
	GETTOR(SHARED(Engine::CGraphicsComponent), m_pGraphics, nullptr, Graphics)
	GETTOR_SETTOR(_float, m_moveSpeed, {}, MoveSpeed)
	GETTOR_SETTOR(_float, m_jumpForce, {}, JumpForce)

	SHARED(Engine::CTransformComponent) m_spCamTransform;

	
};

#endif

// ��� �� �÷��̾�� ��ȣ�ۿ�, �浹 ���� (�÷��̾� ���� �ȵ�)
// 