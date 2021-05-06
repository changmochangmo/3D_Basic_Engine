#ifndef MATHHELPER_H
#define MATHHELPER_H

BEGIN(CMath)
USING(Engine)
class ENGINE_DLL CMathHelper final
{
	DECLARE_SINGLETON(CMathHelper)
public:
	_float		Max					(_float num, _float standard);
	_float		Min					(_float num, _float standard);
	_float		MinMax				(_float num, _float stdMin, _float stdMax);

	_float		UpperRoundOff		(_float num, _float stdMax);
	_float		LowerRoundOFf		(_float num, _float stdMin);
	_float		RoundOffRange		(_float num, _float absRange);

	_float3		AddX				(_float3& vec, _float num);
	_float3		AddY				(_float3& vec, _float num);
	_float3		AddZ				(_float3& vec, _float num);

	_float3		QuatToRad			(_quat& Q);
	_float3		QuatToDegree		(_quat& Q);

	_bool		SeparateAxisTest	(_float3 const& axis, 
									 _float const& minA, _float const& maxA, 
									 _float const& minB, _float const& maxB);
private:
	void		OnDestroy		(void);
};
END

#endif