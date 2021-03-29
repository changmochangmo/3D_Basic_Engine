#include "EngineStdafx.h"
#include "MathHelper.h"

USING(CMath)
IMPLEMENT_SINGLETON(CMathHelper)
_float CMathHelper::Max(_float num, _float standard)
{
	return (num = (num > standard) ? standard : num);
}

_float CMathHelper::Min(_float num, _float standard)
{
	return (num = (num < standard) ? standard : num);
}

void CMathHelper::AddX(_float3 & vec, _float num)
{
	vec.x += num;
}

void CMathHelper::AddY(_float3 & vec, _float num)
{
	vec.y += num;
}

void CMathHelper::AddZ(_float3 & vec, _float num)
{
	vec.z += num;
}

void CMathHelper::OnDestroy(void)
{
}
