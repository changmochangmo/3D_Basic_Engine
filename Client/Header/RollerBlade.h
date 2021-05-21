#ifndef ROLLERBLADE_H
#define ROLLERBLADE_H

#include "Object.h"

class CRollerBlade final : public Engine::CObject	
{
	SMART_DELETER_REGISTER
private:
	explicit						CRollerBlade		(void);
								   ~CRollerBlade		(void);

public:
	static		SP(CRollerBlade)	Create				(_bool isStatic);

				SP(Engine::CObject)	MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

				void				SetBasicName		(void) override;

public:
				void				OnCollisionEnter	(Engine::_CollisionInfo ci);
				void				OnCollisionStay		(Engine::_CollisionInfo ci);
				void				OnCollisionExit		(Engine::_CollisionInfo ci);

private:
	static		_uint						m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,				nullptr,		Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,			nullptr,		Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,			nullptr,		Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,			nullptr,		Collision)
	GETTOR		(SP(Engine::CRigidBodyC),	m_spRigidBody,			nullptr,		RigidBody)
	

	GETTOR		(_mat*,						m_pParentBoneMatrix,	{},				ParentBoneMatrix)
	GETTOR		(const _mat*,				m_pParentWorldMatrix,	{},				ParentWorldMatrix)
		
	GETTOR_SETTOR	(_float,				m_speed,				500.f,			Speed)

	GETTOR_SETTOR	(Engine::CObject*,		m_pBoss,				nullptr,		Boss)
	GETTOR_SETTOR	(Engine::CTransformC*,	m_pPlayerTransform,		nullptr,		PlayerTransform)

	GETTOR_SETTOR	(_float3,				m_targetPos,			ZERO_VECTOR,	TargetPos)
	GETTOR_SETTOR	(_bool,					m_isRightHand,			true,			IsRightHand)
	GETTOR_SETTOR	(_bool,					m_isOnHand,				true,			IsOnHand)
	GETTOR_SETTOR	(_bool,					m_isHoming,				false,			IsHoming)
	GETTOR_SETTOR	(_bool,					m_isCharging,			false,			IsCharging)
	
	GETTOR_SETTOR	(_float,				m_chargeTimer,			0,				HomingTimer)
	GETTOR_SETTOR	(_float,				m_chargeDuration,		2.f,			HomingDuration)
};

#endif