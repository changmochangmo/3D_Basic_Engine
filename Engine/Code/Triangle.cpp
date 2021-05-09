#include "EngineStdafx.h"
#include "Triangle.h"


USING(Engine)
CTriangle::CTriangle()
{
}

CTriangle::CTriangle(_float givenX0, _float givenY0, _float givenZ0, 
					 _float givenX1, _float givenY1, _float givenZ1, 
					 _float givenX2, _float givenY2, _float givenZ2)
{
	point[0] = _float3(givenX0, givenY0, givenZ0);
	point[1] = _float3(givenX1, givenY1, givenZ1);
	point[2] = _float3(givenX2, givenY2, givenZ2);
}

CTriangle::CTriangle(const _float3 & p0, const _float3 & p1, const _float3 & p2)
{
	point[0] = p0;
	point[1] = p1;
	point[2] = p2;
}

CTriangle::CTriangle(const CTriangle & triangle)
{
	point[0] = triangle.point[0];
	point[1] = triangle.point[1];
	point[2] = triangle.point[2];
}


CTriangle::~CTriangle()
{
}

void CTriangle::ClosestFromPoint(_float3 * pOut, const _float3 * p)
{
	_float3 ab = point[1] - point[0];
	_float3 ac = point[2] - point[0];
	_float3 ap = *p - point[0];

	_float d1 = D3DXVec3Dot(&ab, &ap);
	_float d2 = D3DXVec3Dot(&ac, &ap);
	if (d1 <= 0.f && d2 <= 0.f) *pOut = point[0];

	_float3 bp = *p - point[1];
	_float d3 = D3DXVec3Dot(&ab, &bp);
	_float d4 = D3DXVec3Dot(&ac, &bp);
	if (d3 >= 0.f && d4 <= d3) *pOut = point[1];

	_float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.f && d1 >= 0.f && d3 <= 0.f)
	{
		_float v = d1 / (d1 - d3);
		*pOut = point[0] + v * ab;
		return;
	}

	_float3 cp = *p - point[2];
	_float d5 = D3DXVec3Dot(&ab, &cp);
	_float d6 = D3DXVec3Dot(&ac, &cp);
	if (d6 >= 0.f && d5 <= d6) *pOut = point[2];

	_float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.f && d2 >= 0.f && d6 <= 0.f)
	{
		_float w = d2 / (d2 - d6);
		*pOut = point[0] + w * ac;
		return;
	}

	_float va = d3 * d6 - d5 * d4;
	if (va <= 0.f && (d4 - d3) >= 0.f && (d5 - d6) >= 0.f)
	{
		_float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*pOut = point[1] + w * (point[2] - point[1]);
		return;
	}


	_float denominator = 1.f / (va + vb + vc);
	_float v = vb * denominator;
	_float w = vc * denominator;


	*pOut = point[0] + ab * v + ac * w; // = uA + vB + wC, u = va * denominator = 1 - v - w;
}

_float CTriangle::Area(void)
{
	_float3 ab = point[1] - point[0];
	_float3 ac = point[2] - point[0];

	_float3 cross;
	D3DXVec3Cross(&cross, &ab, &ac);
	
	return D3DXVec3Length(&cross) / 2.f;
}

CTriangle & CTriangle::operator=(const CTriangle & rhs)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
}
