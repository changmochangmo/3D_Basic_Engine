#ifndef DoorComponent_H
#define DoorComponent_H

#include "MainComponent.h"

class Engine::CGameObject;
class CDoor final : public Engine::CMainComponent
{
public:
	CDoor();
	virtual ~CDoor();

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
	void DoorActivation();
public:
	static const	EComponentID	m_s_componentID = EComponentID::Door;

protected:
	GETTOR_SETTOR(std::vector<Engine::CGameObject*>, m_pQube, {}, Qube)
	GETTOR_SETTOR(_bool, m_enalbe, true, Enable)
	_bool m_activation = false;
	_float m_endTime = 0.3f;
	_float m_timer = 0;
};

#endif