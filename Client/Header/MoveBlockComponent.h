#ifndef MOVEBLOCK_H
#define MOVEBLOCK_H

#include "EventBlockComponent.h"
class CMoveBlockComponent final : public CEventBlockComponent
{
public:
	explicit			CMoveBlockComponent		(void);
					   ~CMoveBlockComponent		(void);

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
	static const	EComponentID		m_s_componentID = EComponentID::BlueBlock;
private:
	_float m_speed;
	GETTOR_SETTOR(_bool, m_isInteractBlockWithLBtn, false, CheckInteractBlockWithLBtn); // 블럭 상호작용으로 클릭 여부
	GETTOR_SETTOR(_bool, m_isInteractBlockWithRBtn, false, CheckInteractBlockWithRBtn); // 블럭 상호작용으로 클릭 여부

	_bool m_enalbe = true;

	_float3 m_oldPos;
	GETTOR_SETTOR(_float3, m_goalPos, {}, GoalPos);
	SHARED(Engine::CGameObject) m_pObj;
	_float3 m_moveDir[4];
	_int m_moveType;
};

#endif