#ifndef LINE_H
#define LINE_H

BEGIN(Engine)
class CLine
{
public:
	explicit					CLine				(void);
								CLine				(_float givenX1, _float givenY1, _float givenZ1,
													 _float givenX2, _float givenY2, _float givenZ2);
								CLine				(const _float3& p1, const _float3& p2);
								CLine				(const CLine& line);
							   ~CLine				(void);

public:
				void			ClosestFromPoint	(_float3* pOut, const _float3* p);

				_float			Length				(void);
				CLine&			operator =			(const CLine& rhs);
public:
				_float3			point[2];
};
END
#endif