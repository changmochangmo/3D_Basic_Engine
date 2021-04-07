#ifndef ENGINE_STDAFX_H
#define ENGINE_STDAFX_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4503)

//프로젝트 외부 참조문서
//For C, window 
#define NOMINMAX
#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

//For Containers
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <stack>
#include <queue>
#include <array>

//For FileStream
#include <fstream>
#include <sstream>
#include <string>


//For strings
#include <sstream>
#include <string>
#include <codecvt>

//For pointers
#include <memory>

//For function pointers
#include <functional>

//For Algorithm
#include <algorithm>

//For Graphics
#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")


//프로젝트 내의 참조문서
#include "EngineTypedef.h"
#include "EngineDefine.h"
#include "EngineEnum.h"
#include "EngineFunction.h"
#include "EngineExtern.h"
#include "EngineMacro.h"
#include "EngineStructure.h"
#include "EngineComponents.h"

#include "MathHelper.h"
//

// 사운드
#include <io.h>
#include "fmod.h"
#pragma comment (lib, "fmodex64_vc.lib")

#endif