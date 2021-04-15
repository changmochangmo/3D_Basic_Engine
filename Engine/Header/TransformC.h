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
					SP(CComponent)		MakeClone			(CObject* pObject) override;

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
					void				SetSize				(_float3 size);

					void				SetForward			(_float3 lookAt);

					void				AddPosition			(_float3 position);
					void				AddPositionX		(_float adder);
					void				AddPositionY		(_float adder);
					void				AddPositionZ		(_float adder);

					void				AddRotation			(_float3 rotation);
					void				AddRotationX		(_float adder);
					void				AddRotationY		(_float adder);
					void				AddRotationZ		(_float adder);

					void				AddSize				(_float3 size);
					void				AddSizeX			(_float adder);
					void				AddSizeY			(_float adder);
					void				AddSizeZ			(_float adder);

//Interface
public:
					void				MoveForward			(_float magnitude);
					void				MoveBackward		(_float magnitude);
					void				MoveLeft			(_float magnitude);
					void				MoveRight			(_float magnitude);
					void				MoveUp				(_float magnitude);
					void				MoveDown			(_float magnitude);
	
public:
					void				UpdateForward		(void);
					void				UpdateRotation		(void);
					void				UpdateWorldMatrix	(void);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Transform;

protected:
	GETTOR			(_mat,				m_worldMat,		{},				WorldMatrix)

	GETTOR			(_float3,			m_forward,		FORWARD_VECTOR,	Forward)
	GETTOR			(_float3,			m_up,			UP_VECTOR,		Up)
	GETTOR			(_float3,			m_right,		RIGHT_VECTOR,	Right)

	GETTOR			(_float3,			m_position,		ZERO_VECTOR,	Position)
	GETTOR			(_float3,			m_rotation,		ZERO_VECTOR,	Rotation)
	GETTOR			(_float3,			m_size,			ONE_VECTOR,		Size)

	GETTOR			(_bool,				m_hasChanged,	true,			HasChanged)
};
END
#endif