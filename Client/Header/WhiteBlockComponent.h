#ifndef WHITEBLOCK_H
#define WHITEBLOCK_H

#include "NormalBlockComponent.h"

class CWhiteBlockComponent final : public CNormalBlockComponent
{
public:
	explicit		CWhiteBlockComponent		(void);
				   ~CWhiteBlockComponent		(void) = default;

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

public:
	static const	EComponentID		m_s_componentID = EComponentID::WhiteBlock;
};
#endif