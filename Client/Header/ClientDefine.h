#ifndef CLIENTDEFINE_H
#define CLIENTDEFINE_H

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#endif // !CLIENTDEFINE_H
