#ifndef TRIANGLE_H
#define TRIANGLE_H

BEGIN(Engine)
class CTriangle
{
public:
	explicit					CTriangle			(void);
								CTriangle			(_float givenX1, _float givenY1, _float givenZ1,
													 _float givenX2, _float givenY2, _float givenZ2,
													 _float givenX3, _float givenY3, _float givenZ3);
								CTriangle			(const _float3& p1, const _float3& p2);
								CTriangle			(const CLine& line);
							   ~CTriangle			(void);

public:
				void			ClosestFromPoint	(_float3* pOut, const _float3* point);

				_float			Length				(void);
				CLine&			operator =			(const CLine& rhs);
public:
				_float3			point[2];
};
END
#endif