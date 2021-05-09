#include "EngineStdafx.h"
#include "MathHelper.h"

USING(CMath)
IMPLEMENT_SINGLETON(CMathHelper)
_float CMathHelper::Max(_float num, _float standard)
{
	return (num = (num > standard) ? num : standard);
}

_float CMathHelper::Min(_float num, _float standard)
{
	return (num = (num < standard) ? num : standard);
}

_float CMathHelper::MinMax(_float num, _float stdMin, _float stdMax)
{
	num = Min(num, stdMax);
	num = Max(num, stdMin);
	return num;
}

_float CMathHelper::UpperRoundOff(_float num, _float stdMax)
{
	if (num > stdMax)
		num -= abs(stdMax);

	return num;
}

_float CMathHelper::LowerRoundOFf(_float num, _float stdMin)
{
	if (num < stdMin)
		num += abs(stdMin);

	return num;
}

_float CMathHelper::RoundOffRange(_float num, _float absRange)
{
	num = UpperRoundOff(num, absRange);
	num = LowerRoundOFf(num, -absRange);

	return num;
}

_float3 CMathHelper::AddX(_float3 & vec, _float num)
{
	return vec + _float3(num, 0, 0);
}

_float3 CMathHelper::AddY(_float3 & vec, _float num)
{
	return vec + _float3(0, num, 0);
}

_float3 CMathHelper::AddZ(_float3 & vec, _float num)
{
	return vec + _float3(0, 0, num);
}

_float3 CMathHelper::QuatToRad(_quat & Q)
{
	_float heading, attitude, bank;
	_float test = Q.x*Q.y + Q.z*Q.w;
	if (test > 0.499) { // singularity at north pole
		heading = 2 * atan2(Q.x, Q.w);
		attitude = PI / 2;
		bank = 0;
		return _float3(bank, heading, attitude);
	}
	if (test < -0.499) { // singularity at south pole
		heading = -2 * atan2(Q.x, Q.w);
		attitude = -PI / 2;
		bank = 0;
		return _float3(bank, heading, attitude);
	}
	_float sqx = Q.x*Q.x;
	_float sqy = Q.y*Q.y;
	_float sqz = Q.z*Q.z;
	heading = atan2(2 * Q.y*Q.w - 2 * Q.x*Q.z, 1 - 2 * sqy - 2 * sqz);
	attitude = asin(2 * test);
	bank = atan2(2 * Q.x*Q.w - 2 * Q.y*Q.z, 1 - 2 * sqx - 2 * sqz);

	return _float3(bank, heading, attitude);
}

_float3 CMathHelper::QuatToDegree(_quat & Q)
{
	_float3 result = QuatToRad(Q);
	result.x = D3DXToDegree(result.x);
	result.y = D3DXToDegree(result.y);
	result.z = D3DXToDegree(result.z);

	return result;
}

_bool CMathHelper::SeparateAxisTest(_float3 const& axis, 
									_float const& minA, _float const& maxA,
									_float const& minB, _float const& maxB)
{
	_float axisLengthSquared = D3DXVec3Dot(&axis, &axis);

	//if axis is degenerate to ignore
	if (axisLengthSquared <= EPSILON)
		return true;

	//Calculate two possible overlap ranges
	//left or right
	_float d0 = maxB - minA;//left case
	_float d1 = maxA - minB;//right case

						   //Intervals do not overlap -> no interaction
	if (d0 <= 0.f || d1 <= 0.f)
		return false;

	return true;
}

void CMathHelper::OnDestroy(void)
{
}
