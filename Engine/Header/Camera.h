#ifndef CAMERA_H
#define CAMERA_H

#include "Engine.h"

BEGIN(Engine)
class CFrustum;
class ENGINE_DLL CCamera final : public CEngine
{
private:
	explicit					CCamera		(void);
							   ~CCamera		(void);

public:
	static			CCamera*	Create				(void);
					void		Free				(void);

					void		Awake				(void) override;
					void		Start				(void);

					void		Update				(void);
					void		LateUpdate			(void);
					 
					void		OnDestroy			(void);

					void		OnEnable			(void);
					void		OnDisable			(void);

private:
					void		UpdateViewMatrix	(void);
					void		UpdateProjMatrix	(void);

private:
	GETTOR			(CFrustum*,		m_pFrustum,		nullptr,		Frustum)

	GETTOR_SETTOR	(_bool,			m_enable,		true,			Enable)
	GETTOR_SETTOR	(_bool,			m_deleteThis,	false,			DeleteThis)

	GETTOR_SETTOR	(_mat,			m_viewMat,		{},				ViewMatrix)
	GETTOR_SETTOR	(_mat,			m_projMat,		{},				ProjMatrix)
													
	GETTOR_SETTOR	(_float3,		m_position,		ZERO_VECTOR,	Position)
	GETTOR_SETTOR	(_float3,		m_rotation,		ZERO_VECTOR,	Rotation)

	GETTOR_SETTOR	(_float3,		m_lookAt,		FORWARD_VECTOR,	At)
	GETTOR_SETTOR	(_float3,		m_up,			UP_VECTOR,		Up)
													
	GETTOR_SETTOR	(_float,		m_near,			0.f,			Near)
	GETTOR_SETTOR	(_float,		m_far,			1000.f,			Far)
	GETTOR_SETTOR	(_float,		m_FOV,			45.f,			FOV)
													
	GETTOR_SETTOR	(CGameObject*,	m_pOwner,		nullptr,		Owner)
};
END
#endif