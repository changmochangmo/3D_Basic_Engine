#ifndef MATHHELPER_H
#define MATHHELPER_H

BEGIN(CMath)
USING(Engine)
class ENGINE_DLL CMathHelper final
{
	DECLARE_SINGLETON(CMathHelper)
public:
	_float		Max				(_float num, _float standard);
	_float		Min				(_float num, _float standard);

	_float3		AddX			(_float3& vec, _float num);
	_float3		AddY			(_float3& vec, _float num);
	_float3		AddZ			(_float3& vec, _float num);

	_float3		QuatToRad		(_quat& Q);
	_float3		QuatToDegree	(_quat& Q);

private:
	void		OnDestroy		(void);
};
END

#endif