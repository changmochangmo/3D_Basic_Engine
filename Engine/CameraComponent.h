#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H


BEGIN(Engine)
class ENGINE_DLL CCameraComponent final : public CComponent
{
public:
   explicit							CCameraComponent		(void);
								   ~CCameraComponent		(void);
   
public:
					SHARED(CComponent)  MakeClone			(CGameObject* pObject) override;

					void				Awake				(void) override;
					void				Start				(SHARED(CComponent) spThis) override;
															
					_uint				FixedUpdate			(SHARED(CComponent) spThis) override;
					_uint				Update				(SHARED(CComponent) spThis) override;
					_uint				LateUpdate			(SHARED(CComponent) spThis) override;
															
					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

				void					CameraMove			(void);
				void					CameraRotation		(void);
				_bool					IsInFrustum			(_float3 & position);
private:
				void					MaitrxCalculate		(void);
				void					FrustumUpdate		(void);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Camera;		
	static const    _bool               m_s_isEditorMode = false;
	
	//WTF
	GETTOR(SHARED(CTransformComponent), m_pTransform, nullptr, Transform)

protected:
	GETTOR_SETTOR(_mat, m_matView, {}, ViewMatrix)
	GETTOR_SETTOR(_mat, m_matOrtho, {}, OrthoMatrix)
	GETTOR_SETTOR(_mat, m_matProj, {}, ProjMatrix)

	// ī�޶� �ٶ󺸴°� , ī�޶��� ��� ����
	GETTOR_SETTOR(_float3, m_at, {}, At)
	GETTOR_SETTOR(_float3, m_up, {}, Up)

	// ī�޶��� ��� ��ġ
	GETTOR_SETTOR(POINT, m_centerPt, {}, CenterPt);

	GETTOR_SETTOR(_float, m_moveSpeed, 0, MoveSpeed);
	GETTOR_SETTOR(_float, m_mouseSensitivity, 0, MouseSensitivity);

	GETTOR_SETTOR(_float3, m_tAt, FLOAT3_ZERO, TempAt)
	GETTOR_SETTOR(_float3, m_tUp, FLOAT3_ZERO, TempUp)

	GETTOR_SETTOR(_float, m_near, 0, Near)
	GETTOR_SETTOR(_float, m_far, 0, Far)
	GETTOR_SETTOR(_float, m_fov, 0, Fov)

	GETTOR_SETTOR(_bool, m_isCameraEvent, false, CameraEvent)


	// FREAM���� �������� ��ġ ��ȭ��
	GETTOR(_float2, m_mouseDelta, {}, MouseDelta);
	GETTOR_SETTOR(POINT, m_previousFramePt, {}, PreviousFramePt); // �� �������� ���콺��ġ

	// Frustum Culling�� ���� ���� -------------------------
	D3DXPLANE m_leftPlane;
	D3DXPLANE m_rightPlane;
	D3DXPLANE m_topPlane;
	D3DXPLANE m_bottomPlane;
	D3DXPLANE m_nearPlane;
	D3DXPLANE m_farPlane;
	//------------------------------------------------------
};
END

#endif