#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"

BEGIN(Engine)
class CFrustum;
class CObject;
class ENGINE_DLL CCameraC final : public CComponent
{
	SMART_DELETER_REGISTER
public:
	explicit						CCameraC			(void);
								   ~CCameraC			(void);

public:
					SP(CComponent)	MakeClone			(CObject* pObject) override;
					void			Awake				(void) override;
					void			Start				(SP(CComponent) spThis) override;

					void			FixedUpdate			(SP(CComponent) spThis) override;
					void			Update				(SP(CComponent) spThis) override;
					void			LateUpdate			(SP(CComponent) spThis) override;

					void			OnDestroy			(void) override;

					void			OnEnable			(void) override;
					void			OnDisable			(void) override;
public:
					void			SetNear				(_float nearPlane);
					void			SetFar				(_float farPlane);
					void			SetFOV				(_float FOV);

private:
					void			UpdateViewMatrix	(void);
					void			UpdateProjMatrix	(void);
					void			Move				(void);
					void			Translation			(void);
					void			Rotation			(void);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Camera;

private:
	GETTOR			(CFrustum*,			m_pFrustum,				nullptr,				Frustum)

	GETTOR_SETTOR	(_bool,				m_enable,				true,					Enable)
	GETTOR_SETTOR	(_bool,				m_deleteThis,			false,					DeleteThis)

	GETTOR_SETTOR	(ECameraMode,		m_mode,					ECameraMode::Fixed,		Mode)
	GETTOR_SETTOR	(_bool,				m_moveable,				false,					Moveable)
	GETTOR_SETTOR	(_bool,				m_rotatable,			false,					Rotatable)

	GETTOR_SETTOR	(_mat,				m_viewMat,				{},						ViewMatrix)
	GETTOR_SETTOR	(_mat,				m_projMat,				{},						ProjMatrix)

	GETTOR			(_float,			m_near,					0.1f,					Near)
	GETTOR			(_float,			m_far,					1000.f,					Far)
	GETTOR			(_float,			m_FOV,					45.f,					FOV)

	//For TPS Camera
	GETTOR			(_float3,			m_targetOffset,			_float3(0, 0.5f, 0),	TargetOffset)
	GETTOR			(_float,			m_targetDist,			3.f,					TargetDist)
	GETTOR			(_float,			m_lookAngleRight,		PI/7.f,					LookAngleRight)
	GETTOR			(_float,			m_lookAngleUp,			0.f,					LookAngleUp)



	GETTOR			(SP(CTransformC),	m_spTransform,			nullptr,				Transform)
	GETTOR_SETTOR	(SP(CObject),		m_spTarget,				nullptr,				Target)
	
};
END
#endif













//int main()
//{
//	_float3 up/*, eye*//*, lookAt*/;
//	_mat rotationMatrix;
//	SP(CTransformC) spTargetTransform = m_spTarget->GetTransform();
//
//	up = UP_VECTOR;
//	_float3 m_lookAt = spTargetTransform->GetPosition() + m_targetOffset; // 바라보는 위치는 타겟의 위치
//
//	_float3	vTargetLook;
//	memcpy(&vTargetLook, spTargetTransform->GetForward(), sizeof(_float3));
//	D3DXVec3Normalize(&vTargetLook, &vTargetLook);
//
//	_float3 vInvLook = vTargetLook * -m_targetDist;
//
//	_float3	vTargetRight;
//	memcpy(&vTargetRight, spTargetTransform->GetRight(), sizeof(_float3));
//	D3DXVec3Normalize(&vTargetRight, &vTargetRight);
//
//	/* 임의의 축 회전 */
//	D3DXMatrixRotationAxis(&rotationMatrix, &vTargetRight, m_lookAngleRight);
//	D3DXVec3TransformNormal(&vInvLook, &vInvLook, &rotationMatrix);
//
//	/* 임의의 축 회전2 */
//	_float3	vTargetUp;
//	memcpy(&vTargetUp, spTargetTransform->GetUp(), sizeof(_float3));
//	D3DXVec3Normalize(&vTargetUp, &vTargetUp);
//
//	D3DXMatrixRotationAxis(&rotationMatrix, &vTargetUp, m_lookAngleUp);
//	D3DXVec3TransformNormal(&vInvLook, &vInvLook, &rotationMatrix);
//
//	m_spTransform->SetPosition(vInvLook + spTargetTransform->GetPosition());
//
//	D3DXMatrixLookAtLH(&m_viewMat, &m_spTransform->GetPosition(), &m_lookAt, &m_spTransform->GetUp());
//}