#ifndef MYDEFINE_H
#define MYDEFINE_H

#define DEFAULT = default
#define NONE {}

#ifndef ENGINE_MODE
#define EDITOR_MODE
#endif

//MSG_BOX && ABORT
#define _DEBUG_MSG

//Update Event Define
#define NO_EVENT		0
#define SCENE_CHANGE	1
#define NULL_PARAMETER	2
#define OUT_OF_RANGE	3


#define KEY_LEFT	0x00000001
#define KEY_RIGHT	0x00000002
#define KEY_UP		0x00000004
#define KEY_DOWN	0x00000008
#define KEY_SPACE	0x00000010
#define KEY_RETURN	0x00000020
#define MOUSE_LEFT	0x00000040
#define MOUSE_RIGHT	0x00000080
#define KEY_F1		0x00000100
#define KEY_F2		0x00000200
#define KEY_F3		0x00000400
#define KEY_F4		0x00000800
#define KEY_F5		0x00001000
#define KEY_W		0x00002000
#define KEY_A		0x00004000
#define KEY_S		0x00008000
#define KEY_D		0x00010000
#define KEY_Q		0x00020000
#define KEY_E		0x00040000
#define KEY_1       0x00080000
#define KEY_2       0x00100000
#define KEY_3		0x00200000
#define KEY_4		0x00400000
#define KEY_TAB		0x00800000
#define KEY_DELETE	0x01000000
#define KEY_Z		0x02000000
#define KEY_X		0x04000000

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

#define PLAYER_RAY_DISTANCE 0.7f

#define PI 3.141592f
#define EPSILON 0.0003f

#endif // !MYDEFINE_H
