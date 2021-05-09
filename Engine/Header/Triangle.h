#ifndef TRIANGLE_H
#define TRIANGLE_H

BEGIN(Engine)
class CTriangle
{
public:
	explicit					CTriangle			(void);
								CTriangle			(_float givenX0, _float givenY0, _float givenZ0,
													 _float givenX1, _float givenY1, _float givenZ1,
													 _float givenX2, _float givenY2, _float givenZ2);
								CTriangle			(const _float3& p0, const _float3& p1, const _float3& p2);
								CTriangle			(const CTriangle& triangle);
							   ~CTriangle			(void);

public:
				void			ClosestFromPoint	(_float3* pOut, const _float3* p);
				_float			Area				(void);

				CTriangle&		operator =			(const CTriangle& rhs);
public:
				_float3			point[3];
};
END
#endif