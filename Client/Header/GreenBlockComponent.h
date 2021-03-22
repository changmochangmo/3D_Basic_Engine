#ifndef GREENBLOCK_H
#define GREENBLOCK_H

#include "EventBlockComponent.h"
class CGreenBlockComponent final : public CEventBlockComponent
{
public:
	explicit			CGreenBlockComponent(void);
					   ~CGreenBlockComponent(void);

public:
	SHARED(Engine::CComponent)	MakeClone		(Engine::CGameObject * pObject) override;

	void						Awake			(void) override;
	void						Start			(SHARED(Engine::CComponent) spThis) override;

	_uint						FixedUpdate		(SHARED(Engine::CComponent) spThis) override;
	_uint						Update			(SHARED(Engine::CComponent) spThis) override;
	_uint						LateUpdate		(SHARED(Engine::CComponent) spThis) override;

	void						OnDestroy		(void) override;
	void						OnEnable		(void) override;
	void						OnDisable		(void) override;

	void						LClicked		(void) override;
	void						RClicked		(void) override;

public:
	static const	EComponentID		m_s_componentID = EComponentID::RedBlock;
	Engine::CGameObject* CheckBlocksForRayCollision(_float3 direction);
	_float3 GetBlockDir(_float3 dir);
	_float3 GetDirectionOfMovement(_float3 vAt, _float3 vRotation);

private:
	_float3 m_initialPosition;
	_float3 m_activationPosition;
	Engine::CGameObject* m_curCollidedBlock = nullptr; // 현재 충돌된 블럭
};

#endif