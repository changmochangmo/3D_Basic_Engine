#ifndef BLUEBLOCK_H
#define BLUEBLOCK_H

#include "EventBlockComponent.h"
class CBlueBlockComponent final : public CEventBlockComponent
{
public:
	explicit			CBlueBlockComponent		(void);
					   ~CBlueBlockComponent		(void);

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
	_float3 GetDirectionOfMovement(_float3 vAt, _float3 vRotation);

private:
	_float3 m_force;
	_float3 m_initialPosition;
	_float3 m_activationPosition;
	_float m_speed;
	_float3 m_up;
	_bool m_reload = true;
	Engine::CGameObject* m_pPlayer = nullptr; // �浹�� �÷��̾ ��� ����

	SHARED(Engine::CTransformComponent) pTransformComponent;
	GETTOR_SETTOR(_bool, m_isInteractBlockWithLBtn, false, CheckInteractBlockWithLBtn); // �� ��ȣ�ۿ����� Ŭ�� ����
	GETTOR_SETTOR(_bool, m_isInteractBlockWithRBtn, false, CheckInteractBlockWithRBtn); // �� ��ȣ�ۿ����� Ŭ�� ����
};

#endif