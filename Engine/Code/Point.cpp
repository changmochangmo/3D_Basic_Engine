#include "EngineStdafx.h"
#include "Point.h"


USING(Engine)

CPoint::CPoint(void)
{
}

CPoint::CPoint(_float givenX, _float givenY, _float givenZ)
	: x(givenX), y(givenY), z(givenZ)
{
}

CPoint::CPoint(const CPoint & point)
	: x(point.x), y(point.y), z(point.z)
{
}

CPoint::CPoint(const _float3 & point)
	: x(point.x), y(point.y), z(point.z)
{
}

CPoint::~CPoint(void)
{
}

D3DXVECTOR3 CPoint::ToD3DXVEC3(void)
{
	return D3DXVECTOR3(x, y, z);
}

CPoint& CPoint::Normalize(void)
{
	if (abs(x) < EPSILON && abs(y) < EPSILON && abs(y) < EPSILON)
		return;

	_float length = sqrtf(x * x + y * y + z * z);
	
	return (*this /= length);
}

_bool CPoint::operator==(const CPoint & rhs)
{
	if (x == rhs.x &&
		y == rhs.y &&
		z == rhs.z)
		return true;

	return false;
}

CPoint & CPoint::operator=(const CPoint & rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

CPoint & CPoint::operator=(const _float3 & rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

CPoint CPoint::operator+(const CPoint & rhs) const
{
	return CPoint(x + rhs.x, y + rhs.y, z + rhs.z);
}

CPoint CPoint::operator-(const CPoint & rhs) const
{
	return CPoint(x - rhs.x, y - rhs.y, z - rhs.z);
}

CPoint::operator _float3(void) const
{
	return _float3(x, y, z);
}

CPoint& CPoint::operator/(_float rhs)
{
	if (abs(rhs) < EPSILON)
	{
		MSG_BOX(__FILE__, L"Devide by Zero");
		ABORT;
	}

	x = x / rhs;
	y = y / rhs;
	z = z / rhs;

	return *this;
}

CPoint& CPoint::operator/=(_float rhs)
{
	*this = *this / rhs;
	return *this;
}
