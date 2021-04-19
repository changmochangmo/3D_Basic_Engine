#ifndef ENGINETYPEDEF_H
#define ENGINETYPEDEF_H

namespace Engine
{
	typedef bool			_bool;

	typedef char			_byte;
	typedef unsigned char	_ubyte;

	typedef wchar_t			_tchar;

	typedef int				_int;
	typedef unsigned int	_uint;

	typedef	signed long		_long;
	typedef unsigned long	_ulong;

	typedef size_t			_size;

	typedef float			_float;
	typedef double			_double;

	typedef D3DXVECTOR2		_float2;
	typedef D3DXVECTOR3		_float3;
	typedef D3DXVECTOR4		_float4;

	typedef D3DXMATRIX		_mat;
	typedef D3DXQUATERNION	_quat;
}
#endif // ENGINETYPEDEF_H
