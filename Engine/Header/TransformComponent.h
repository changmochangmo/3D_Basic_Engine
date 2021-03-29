#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTransformComponent final : public CComponent
{
public:
	explicit							CTransformComponent	(void);
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

private:
					void				UpdateWorldmMatrix	(void);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Transform;

protected:
	GETTOR_SETTOR	(_mat,				m_worldMat,		{},					WorldMatrix)
	GETTOR_SETTOR	(_float3,			m_position,		_float3(0,0,0),		Position)
	GETTOR_SETTOR	(_float3,			m_rotation,		_float3(0,0,0),		Rotation)
	GETTOR_SETTOR	(_float3,			m_scale,		_float3(1,1,1),		Scale)

	
};
END
#endif