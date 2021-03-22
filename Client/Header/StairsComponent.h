#ifndef StairsComponent_H
#define StairsComponent_H

#include "MainComponent.h"

class Engine::CGameObject;
class CStairsComponent final : public Engine::CMainComponent
{
public:
	explicit CStairsComponent();
	virtual ~CStairsComponent();

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

	void Init(_int width, _int height);
private:
	void StairsActivation();
public:
	static const	EComponentID	m_s_componentID = EComponentID::Stairs;
protected:
	GETTOR_SETTOR(_int, m_width, 0, Width)
	GETTOR_SETTOR(_int, m_height, 0, Height)
	GETTOR_SETTOR(std::vector<SHARED(Engine::CGameObject)>, m_pStairs, {}, Stairs)
	std::vector<_float3> m_vCurPos;
	_int hitBlock = INT_MAX;
	_bool m_activation = false;
	_bool m_stairsActivation = true;
};

#endif