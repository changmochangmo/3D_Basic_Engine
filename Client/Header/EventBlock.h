#pragma once


class CEventBlockComponent;
class Engine::CGameObject;
class Engine::CTransformComponent;
class CEventBlock
{
public:
	CEventBlock();
	~CEventBlock();

public:
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void LClicked() = 0;
	virtual void RClicked() = 0;
protected:
	GETTOR_SETTOR(CEventBlockComponent*, m_pEventBlockComponent, {}, EventBlockComponent);
	GETTOR_SETTOR(SHARED(Engine::CTransformComponent), m_pTransformComponent, {}, TransformComponent);
	GETTOR_SETTOR(Engine::CGameObject*, m_pGameObject, {}, GameObject);
};

