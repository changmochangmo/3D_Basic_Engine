#ifndef ElevatorComponent_H
#define ElevatorComponent_H

#include "MainComponent.h"

class Engine::CGameObject;
class CElevator final : public Engine::CMainComponent
{
public:
	CElevator();
	virtual ~CElevator();

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

	void Init(_int width, _int height, _int downDepth);
private:
	void ElevatorActivation();

public:
	static const	EComponentID	m_s_componentID = EComponentID::Elevator;
protected:
	GETTOR_SETTOR(_int, m_width, 0, Width)
	GETTOR_SETTOR(_int, m_height, 0, Height)
	GETTOR_SETTOR(std::vector<Engine::CGameObject*>, m_pQube, {}, Qube)
	GETTOR_SETTOR(_int, m_downDepth, 0, DownDepth)
	std::vector<_float3> m_vGoalPos;
	_bool m_activation = false;
	_bool m_end = false;
	Engine::CGameObject* m_playerObj;
};

#endif