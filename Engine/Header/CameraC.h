#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"

BEGIN(Engine)
class CFrustum;
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
	GETTOR			(CFrustum*,			m_pFrustum,		nullptr,				Frustum)

	GETTOR_SETTOR	(_bool,				m_enable,		true,					Enable)
	GETTOR_SETTOR	(_bool,				m_deleteThis,	false,					DeleteThis)

	GETTOR_SETTOR	(ECameraMode,		m_mode,			ECameraMode::Fixed,		Mode)
	GETTOR_SETTOR	(_bool,				m_moveable,		false,					Moveable)
	GETTOR_SETTOR	(_bool,				m_rotatable,	false,					Rotatable)

	GETTOR_SETTOR	(_bool,				m_updateProj,	true,					UpdateProj)
	GETTOR_SETTOR	(_bool,				m_updateView,	true,					UpdateView)

	GETTOR_SETTOR	(_mat,				m_viewMat,		{},						ViewMatrix)
	GETTOR_SETTOR	(_mat,				m_projMat,		{},						ProjMatrix)

	GETTOR			(_float,			m_near,			0.1f,					Near)
	GETTOR			(_float,			m_far,			1000.f,					Far)
	GETTOR			(_float,			m_FOV,			45.f,					FOV)

	GETTOR			(SP(CTransformC),	m_spTransform,	nullptr,				Transform)
													
	
};
END
#endif