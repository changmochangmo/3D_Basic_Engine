#ifndef EVENTBLOCKCOMPONENT_H
#define EVENTBLOCKCOMPONENT_H

#include "BlockComponent.h"

class Engine::CGameObject;
class CEventBlockComponent abstract : public CBlockComponent
{
public:
	explicit	CEventBlockComponent		(void);
	virtual	   ~CEventBlockComponent		(void);

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

private:
	virtual		void						LClicked		(void) PURE;
	virtual		void						RClicked		(void) PURE;


protected:
	GETTOR_SETTOR	(_int,		m_activatedLv,		0,		ActivatedLv)
	GETTOR			(_int,		m_maxActivatedLv,	-1,		MaxActivatedLv)

	GETTOR_SETTOR	(_bool, m_lButton, true, LButton);
	GETTOR_SETTOR	(_bool, m_rButton, false, RButton);
};

#endif