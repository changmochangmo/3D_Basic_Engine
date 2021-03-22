#ifndef PLAYER_H
#define PLAYER_H

#include "MainComponent.h"

class Engine::CGameObject;
class CPlayer final : public Engine::CMainComponent
{
public:
	explicit	CPlayer		(void);
			   ~CPlayer		(void);

public:
	SHARED(Engine::CComponent)	MakeClone		(Engine::CGameObject * pObject);
	
	void						Awake			(void) override;
	void						Start			(SHARED(CComponent) spThis) override;
	
	_uint						FixedUpdate		(SHARED(CComponent) spThis) override;
	_uint						Update			(SHARED(Engine::CComponent) spSelf) override;
	_uint						LateUpdate		(SHARED(Engine::CComponent) spSelf) override;
	
	void						OnDestroy		(void) override;
	void						OnEnable		(void) override;
	void						OnDisable		(void) override;
private:
	void Move();

protected:

};

#endif