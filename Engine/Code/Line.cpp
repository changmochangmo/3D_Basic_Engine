#include "EngineStdafx.h"
#include "Line.h"


USING(Engine)
CLine::CLine()
{
}

CLine::CLine(_float givenX1, _float givenY1, _float givenZ1, _float givenX2, _float givenY2, _float givenZ2)
{
	point[0] = _float3(givenX1, givenY1, givenZ1);
	point[1] = _float3(givenX2, givenY2, givenZ2);
}

CLine::CLine(const _float3 & p1, const _float3 & p2)
{
	point[0] = p1;
	point[1] = p2;
}

CLine::CLine(const CLine & line)
{
	point[0] = line.point[0];
	point[1] = line.point[1];
}


CLine::~CLine()
{
}

void CLine::ClosestFromPoint(_float3* pOut, const _float3* point)
{
	_float3 ab = point[1] + point[0];

	//u + v = 1
	//u * A + v * B = point를 AB직선에 투영시킨 점.
	//Baricentric coordinates
	_float v = D3DXVec3Dot(&(*point - point[0]), &ab) / D3DXVec3Dot(&ab, &ab);

	GET_MATH->LowerRoundOFf(v, 0);
	GET_MATH->UpperRoundOff(v, 1);

	//intersection = (1-v)A + vB = uA + vB
	*pOut = point[0] + v * ab;
}

_float CLine::Length(void)
{
	if (point[0] == point[1])
		return 0;

	return sqrtf((point[1].x - point[0].x) * (point[1].x - point[0].x) +
				 (point[1].y - point[0].y) * (point[1].y - point[0].y) +
				 (point[1].z - point[0].z) * (point[1].z - point[0].z));
}

CLine & CLine::operator=(const CLine & rhs)
{
	point[0] = rhs.point[0];
	point[1] = rhs.point[1];

	return *this;
}
