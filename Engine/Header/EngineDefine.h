#ifndef MYDEFINE_H
#define MYDEFINE_H

#define DEFAULT = default
#define NONE {}

#ifndef ENGINE_MODE
#define EDITOR_MODE
#endif

//MSG_BOX && ABORT
#define _DEBUG_MSG

//Enum define
#define UNDEFINED -1

//NewLine
#define NEW_LINE L'\n'


#define KEY_LEFT	1 << 0
#define KEY_RIGHT	1 << 1
#define KEY_UP		1 << 2
#define KEY_DOWN	1 << 3
#define KEY_SPACE	1 << 4
#define KEY_CONTROL	1 << 5
#define MOUSE_LEFT	1 << 6
#define MOUSE_RIGHT	1 << 7
#define KEY_F1		1 << 8
#define KEY_F2		1 << 9
#define KEY_F3		1 << 10
#define KEY_F4		1 << 11
#define KEY_F5		1 << 12
#define KEY_W		1 << 13
#define KEY_A		1 << 14
#define KEY_S		1 << 15
#define KEY_D		1 << 16
#define KEY_Q		1 << 17
#define KEY_E		1 << 18
#define KEY_1       1 << 19
#define KEY_2       1 << 20
#define KEY_3		1 << 21
#define KEY_4		1 << 22
#define KEY_TAB		1 << 23
#define KEY_SHIFT	1 << 24
#define KEY_Z		1 << 25
#define KEY_X		1 << 26

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define GRAVITY			_float3(0,  -9.807f, 0)

#define ZERO_VECTOR		_float3(0,  0,  0)
#define ONE_VECTOR		_float3(1,  1,  1)
#define RIGHT_VECTOR	_float3(1,  0,  0)
#define LEFT_VECTOR		_float3(-1, 0,  0)
#define UP_VECTOR		_float3(0,  1,  0)
#define DOWN_VECTOR		_float3(0,  -1, 0)
#define FORWARD_VECTOR	_float3(0,  0,  1)
#define BACK_VECTOR		_float3(0,  0, -1)
#define MAX_VECTOR		_float3(FLT_MAX, FLT_MAX, FLT_MAX)

#define PLAYER_RAY_DISTANCE 0.7f

#define PI 3.141592f
#define EPSILON 0.0003f

#endif // !MYDEFINE_H
