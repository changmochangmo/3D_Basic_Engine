#ifndef NORMALBLOCKCOMPONENT_H
#define NORMALBLOCKCOMPONENT_H

#include "BlockComponent.h"

class Engine::CGameObject;
class CNormalBlockComponent abstract : public CBlockComponent	
{
public:
	explicit		CNormalBlockComponent		(void);
	virtual		   ~CNormalBlockComponent		(void);

public:
	virtual		SHARED(Engine::CComponent)	MakeClone		(Engine::CGameObject * pObject) PURE;

	virtual		void						Awake			(void) PURE;
	virtual		void						Start			(SHARED(Engine::CComponent) spThis) PURE;

	virtual		_uint						FixedUpdate		(SHARED(Engine::CComponent) spThis) PURE;
	virtual		_uint						Update			(SHARED(Engine::CComponent) spThis) PURE;
	virtual		_uint						LateUpdate		(SHARED(Engine::CComponent) spThis) PURE;

	virtual		void						OnDestroy		(void) PURE;
	virtual		void						OnEnable		(void) PURE;
	virtual		void						OnDisable		(void) PURE;
};

#endif