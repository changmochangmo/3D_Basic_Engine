#ifndef FRUSTUM_H
#define FRUSTUM_H

BEGIN(Engine)
class CCamera;
class ENGINE_DLL CFrustum final
{
private:
	explicit					CFrustum			(void);
							   ~CFrustum			(void);

public:
	static			CFrustum*	Create				(CCamera* pOwner);
					void		Free				(void);

					void		Awake				(void);
					void		Update				(void);
					void		LateUpdate			(void);

					void		OnEnable			(void);
					void		OnDisable			(void);

					_bool		CheckPoint			(_float3 position);
					_bool		CheckAabb			(_float3 position, _float3 halfExtent);
					_bool		CheckSphere			(_float3 position, _float radius);
private:
					void		OnDestroy			(void);

private:
					D3DXPLANE		m_plane[6];

	GETTOR_SETTOR	(CCamera*,		m_pOwner,		nullptr,	Owner)
};
END

#endif