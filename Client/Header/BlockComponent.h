#ifndef BLOCKCOMPONENT_H
#define BLOCKCOMPONENT_H

#include "MainComponent.h"

class Engine::CGameObject;
class CBlockComponent abstract : public Engine::CMainComponent
{
public:
	explicit		CBlockComponent		(void);
	virtual		   ~CBlockComponent		(void);

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