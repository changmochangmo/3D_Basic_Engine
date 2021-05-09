#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTransformC final : public CComponent
{
public:
	explicit							CTransformC				(void);
									   ~CTransformC				(void);

//Override functions									   
public:
					SP(CComponent)		MakeClone				(CObject* pObject) override;

					void				Awake					(void) override;
					void				Start					(SP(CComponent) spThis) override;

					void				FixedUpdate				(SP(CComponent) spThis) override;
					void				Update					(SP(CComponent) spThis) override;
					void				LateUpdate				(SP(CComponent) spThis) override;

					void				OnDestroy				(void) override;

					void				OnEnable				(void) override;
					void				OnDisable				(void) override;

//Settors
#pragma region Settors
public:
					void				SetPosition				(_float3 position);
					void				SetPosition				(_float posX, _float posY, _float posZ);
					void				SetPositionX			(_float posX);
					void				SetPositionY			(_float posY);
					void				SetPositionZ			(_float posZ);

					void				SetRotation				(_float3 rotation);
					void				SetRotation				(_float rotX, _float rotY, _float rotZ);
					void				SetRotationX			(_float rotationX);
					void				SetRotationY			(_float rotationY);
					void				SetRotationZ			(_float rotationZ);

					void				SetSize					(_float3 size);
					void				SetSize					(_float sizeX, _float sizeY, _float sizeZ);
					void				SetSizeX				(_float sizeX);
					void				SetSizeY				(_float sizeY);
					void				SetSizeZ				(_float sizeZ);

					void				AddPosition				(_float3 position);
					void				AddPositionX			(_float adder);
					void				AddPositionY			(_float adder);
					void				AddPositionZ			(_float adder);

					void				AddRotation				(_float3 rotation);
					void				AddRotationX			(_float adder);
					void				AddRotationY			(_float adder);
					void				AddRotationZ			(_float adder);

					void				AddSize					(_float3 size);
					void				AddSizeX				(_float adder);
					void				AddSizeY				(_float adder);
					void				AddSizeZ				(_float adder);

					void				SetForward				(_float3 lookAt);

#pragma endregion
//Interface
public:
					void				SlerpXZ					(void);
					void				MoveForward				(_float magnitude);
					void				MoveBackward			(_float magnitude);
					void				MoveLeft				(_float magnitude);
					void				MoveRight				(_float magnitude);
					void				MoveUp					(_float magnitude);
					void				MoveDown				(_float magnitude);

					void				CopyTransform			(CTransformC const& transform);
	
					void				operator =				(CTransformC const& rhs);
public:
					void				UpdateForward			(void);
					void				UpdateRotation			(void);
					void				UpdateWorldMatrix		(void);


					
					

public:
	static const	EComponentID		m_s_componentID = EComponentID::Transform;

protected:
	GETTOR			(_mat,			m_worldMat,					{},					WorldMatrix)
	GETTOR			(_mat,			m_worldMatNoScale,			{},					WorldMatrixNoScale)

	//Mine
	GETTOR			(_float3,		m_forward,					FORWARD_VECTOR,		Forward)
	GETTOR			(_float3,		m_up,						UP_VECTOR,			Up)
	GETTOR			(_float3,		m_right,					RIGHT_VECTOR,		Right)

	GETTOR_SETTOR	(_float3,		m_goalForward,				ZERO_VECTOR,		GoalForward)
	GETTOR			(_float,		m_slerpSpeed,				PI / 0.5f,			SlerpSpeed)

	GETTOR			(_float3,		m_position,					ZERO_VECTOR,		Position)
	GETTOR			(_float3,		m_rotation,					ZERO_VECTOR,		Rotation)
	GETTOR			(_float3,		m_size,						ONE_VECTOR,			Size)

	//My size * mesh size
	GETTOR			(_float3,		m_finalSize,				ONE_VECTOR,			FinalSize)
};
END
#endif