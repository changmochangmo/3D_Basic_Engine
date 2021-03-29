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

	void		AddX			(_float3& vec, _float num);
	void		AddY			(_float3& vec, _float num);
	void		AddZ			(_float3& vec, _float num);
private:
	void		OnDestroy		(void);
};
END

#endif