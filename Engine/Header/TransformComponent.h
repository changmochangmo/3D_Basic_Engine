#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTransformComponent final : public CComponent
{
public:
	explicit	CTransformComponent	(void);
			   ~CTransformComponent	(void);
public:
					SHARED(CComponent)	MakeClone			(CGameObject* pObject) override;

					void				Awake				(void) override;
					void				Start				(SHARED(CComponent) spThis) override;

					_uint				FixedUpdate			(SHARED(CComponent) spThis) override;
					_uint				Update				(SHARED(CComponent) spThis) override;
					_uint				LateUpdate			(SHARED(CComponent) spThis) override;

					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

					void				Translate			(_float3 translation);
					void				MoveTowards			(_float3& thisPosition, _float3 targetPosition, _float speed);
					void				Lerp				(_float3& thisPosition, _float3 targetPosition, _float speed);

					void				SetPositionX		(_float x) { m_position.x = x; }
					void				SetPositionY		(_float y) { m_position.y = y; }
					void				SetPositionZ		(_float z) { m_position.z = z; }

					void				AddPosition			(_float3 xyz) { m_position += xyz; }
					void				AddPositionX		(_float x) { m_position.x += x; }
					void				AddPositionY		(_float y) { m_position.y += y; }
					void				AddPositionZ		(_float z) { m_position.z += z; }

					void				SetRotationX		(_float x) { m_rotation.x = x; }
					void				SetRotationY		(_float y) { m_rotation.y = y; }
					void				SetRotationZ		(_float z) { m_rotation.z = z; }

 					void				AddRotationX		(_float x) { m_rotation.x +=  x; }
					void				AddRotationY		(_float y) { m_rotation.y +=  y; }
					void				AddRotationZ		(_float z) { m_rotation.z +=  z; }
private:
					void				UpdateWorldmMatrix	(void);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Transform;

protected:
	GETTOR			(_mat,				m_worldMat,		{},					WorldMatrix)
	GETTOR_SETTOR	(_float3,			m_position,		_float3(0,0,0),		Position) // GetfuncName
	GETTOR_SETTOR	(_float3,			m_rotation,		_float3(0,0,0),		Rotation)
	GETTOR_SETTOR	(_float3,			m_scale,		_float3(1,1,1),		Scale)

	
};
END
#endif