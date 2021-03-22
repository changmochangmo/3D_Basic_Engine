#pragma once
#include "EventBlock.h"
class CBlueBlock :
	public CEventBlock
{
public:
	CBlueBlock();
	virtual ~CBlueBlock();

public:
	static			CBlueBlock*		Create(_float3 force);
	virtual void Awake() override;
	virtual void Start() override;
	virtual void LClicked() override;
	virtual void RClicked() override;

private:
	_float3 m_force;
	_float3 m_initialPosition;
	_float3 m_activationPosition;
	// CEventBlock을(를) 통해 상속됨
};

