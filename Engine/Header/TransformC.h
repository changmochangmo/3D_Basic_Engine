#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTransformC final : public CComponent
{
public:
	explicit							CTransformC	(void);
									   ~CTransformC	(void);

//Override functions									   
public:
					SP(CComponent)		MakeClone			(CGameObject* pObject) override;

					void				Awake				(void) override;
					void				Start				(SP(CComponent) spThis) override;

					void				FixedUpdate			(SP(CComponent) spThis) override;
					void				Update				(SP(CComponent) spThis) override;
					void				LateUpdate			(SP(CComponent) spThis) override;

					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

//Settors
public:
					void				SetPosition			(_float3 position);
					void				SetRotation			(_float3 rotation);
					void				SetScale			(_float3 scale);

					void				SetForward			(_float3 lookAt);

					void				AddPosition			(_float3 position);
					void				AddPositionX		(_float adder);
					void				AddPositionY		(_float adder);
					void				AddPositionZ		(_float adder);

					void				AddRotation			(_float3 rotation);
					void				AddRotationX		(_float adder);
					void				AddRotationY		(_float adder);
					void				AddRotationZ		(_float adder);

					void				AddScale			(_float3 scale);
					void				AddScaleX			(_float adder);
					void				AddScaleY			(_float adder);
					void				AddScaleZ			(_float adder);

//Interface
public:
					void				MoveForward			(_float magnitude);
					void				MoveBackward		(_float magnitude);
					void				MoveLeft			(_float magnitude);
					void				MoveRight			(_float magnitude);
	
public:
					void				UpdateForward		(void);
					void				UpdateRotation		(void);
					void				UpdateWorldMatrix	(void);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Transform;

protected:
	//GETTOR_SETTOR	(SP(CTransformC),	m_spParent,		nullptr,		Parent)
	

	GETTOR			(_mat,				m_worldMat,		{},				WorldMatrix)

	GETTOR			(_float3,			m_forward,		FORWARD_VECTOR,	Forward)
	GETTOR			(_float3,			m_up,			UP_VECTOR,		Up)
	GETTOR			(_float3,			m_right,		RIGHT_VECTOR,	Right)

	GETTOR			(_float3,			m_position,		ZERO_VECTOR,	Position)
	GETTOR			(_float3,			m_rotation,		ZERO_VECTOR,	Rotation)
	GETTOR			(_float3,			m_scale,		ONE_VECTOR,		Scale)

	GETTOR			(_bool,				m_hasChanged,	true,			HasChanged)
};
END
#endif