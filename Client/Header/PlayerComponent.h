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
	void						PlayerMousePicking(); // 플레이어가 마우스 좌우클릭을 통해 블럭과 상호작용하는 함수
	_float3						GetPlayerDir(_float3 dir);
	_bool						CheckBlocksForRayCollision(_float3 direction); // 광선으로 블럭과 충돌하는지 체크. 충돌하면 true 반환

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

// 모든 블럭 플레이어와 상호작용, 충돌 가능 (플레이어 위는 안됨)
// 