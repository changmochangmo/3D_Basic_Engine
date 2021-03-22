#ifndef REDBLOCK_H
#define REDBLOCK_H

#include "EventBlockComponent.h"
class CRedBlockComponent final : public CEventBlockComponent
{
public:
	explicit			CRedBlockComponent(void);
					   ~CRedBlockComponent(void);

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
	static const	EComponentID		m_s_componentID = EComponentID::RedBlock;
	_float3 GetDirectionOfMovement(_float3 vAt, _float3 vRotation);
	_bool CheckBlocksForRayCollision(_float3 direction); // �������� ���� �浹�ϴ��� üũ. �浹�ϸ� true ��ȯ

private:
	GETTOR(_float3, m_initialPosition, {}, InitalPosition);
	GETTOR(_float3, m_activationPosition, {}, ActivationPosition);
	GETTOR_SETTOR(_bool, m_isInteractBlockWithLBtn, false, CheckInteractBlockWithLBtn); // �� ��ȣ�ۿ����� Ŭ�� ����
	GETTOR_SETTOR(_bool, m_isInteractBlockWithRBtn, false, CheckInteractBlockWithRBtn); // �� ��ȣ�ۿ����� Ŭ�� ����
};

#endif