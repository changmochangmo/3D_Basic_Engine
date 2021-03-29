#ifndef ENGINEMATH_H
#define ENGINEMATH_H

BEGIN(Engine)
BEGIN(Math)

inline _float Max(_float num, _float standard)
{
	return (num = (num > standard) ? standard : num);
}

inline _float Min(_float num, _float standard)
{
	return (num = (num < standard) ? standard : num);
}

inline void AddX(_float3& float3, _float num)
{
	float3.x += num;
}

inline void AddY(_float3& float3, _float num)
{
	float3.y += num;
}

inline void AddZ(_float3& float3, _float num)
{
	float3.z += num;
}

END
END

#endif