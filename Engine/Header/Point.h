#ifndef POINT_H
#define POINT_H

BEGIN(Engine)
class CPoint final
{
public:
	explicit					CPoint			(void);
								CPoint			(_float givenX, _float givenY, _float givenZ);
								CPoint			(const CPoint& point);
								CPoint			(const _float3& point);
							   ~CPoint			(void);

public:
				_float3			ToD3DXVEC3		(void);
				CPoint&			Normalize		(void);

				_bool			operator ==		(const CPoint& rhs);
				CPoint&			operator =		(const CPoint& rhs);
				CPoint&			operator =		(const _float3& rhs);

				CPoint			operator +		(const CPoint& rhs) const;

				CPoint			operator -		(const CPoint& rhs) const;

				operator		_float3			(void) const;

				CPoint&			operator /		(_float rhs);
				CPoint&			operator /=		(_float rhs);
public:
				_float	x = 0.f;
				_float	y = 0.f;
				_float	z = 0.f;
};
END

#endif