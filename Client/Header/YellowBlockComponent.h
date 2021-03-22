#pragma once

#include "EventBlockComponent.h"
class CYellowBlockComponent final : public CEventBlockComponent
{
public:
	explicit CYellowBlockComponent();
	~CYellowBlockComponent() = default;

	virtual SHARED(Engine::CComponent) MakeClone(Engine::CGameObject * pObject) override;
	virtual void Awake(void) override;
	virtual void Start(SHARED(Engine::CComponent) spThis) override;
	virtual _uint FixedUpdate(SHARED(Engine::CComponent) spThis) override;
	virtual _uint Update(SHARED(Engine::CComponent) spThis) override;
	virtual _uint LateUpdate(SHARED(Engine::CComponent) spThis) override;
	virtual void OnDestroy(void) override;
	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;
	virtual void LClicked(void) override;
	virtual void RClicked(void) override;

public:
	static const	EComponentID		m_s_componentID = EComponentID::YellowBlock;
	_float3 GetDirectionOfMovement(_float3 vAt, _float3 vRotation);
	_bool CheckBlocksForRayCollision(); // �������� ���� �浹�ϴ��� üũ. �浹�ϸ� true ��ȯ

private:
	//_bool   m_isCubeMoveStart = false;
	//_bool   m_isCubeMoveEnd = false;
	//_int    m_iCnt = 0;
	//_int    m_iPreCnt = 0;
	static _uint m_yellowBlockCnt; // ��� ���� �� ����. �̸� �̿��ؼ� ��� �� ������ �׷� ��ȣ�� �׷� �� ���� ��ȣ�� �ο��Ѵ�.
	_float3 m_initialPosition;
	_float3 m_activationPosition;
	Engine::CGameObject* m_arrBlocks[3] = { nullptr }; // ��� ���� ���� �迭. ������ų ������� ����

	//SHARED(Engine::CGameObject) y0;
	//SHARED(Engine::CGameObject) y1;
	//SHARED(Engine::CGameObject) y2;

	GETTOR_SETTOR(_uint, m_groupNumber, 0, GroupNumber); // ������ �׷� ���ڸ� ������ ������ ������
	GETTOR_SETTOR(_uint, m_orderWithinGroup, 0, OrderWithinGroup); // �׷� ������ ����
	GETTOR_SETTOR(_bool, m_isInteractBlockWithLBtn, false, CheckInteractBlockWithLBtn); // �� ��ȣ�ۿ����� Ŭ�� ����
	GETTOR_SETTOR(_bool, m_isInteractBlockWithRBtn, false, CheckInteractBlockWithRBtn); // �� ��ȣ�ۿ����� Ŭ�� ����

//private:
//	// ť�갡 �����ɽ�Ʈ�� �浹�Ǿ��� �� ���� �Լ�
//	void FirstCubePicking();
//	void SecondCubePicking();
//	void ThirdCubePicking();
//
//	// ť�긦 ������� �������� �Լ�
//	void FirstCubeInit();
//	void SecondCubeInit();
//	void ThirdCubeInit();
};

