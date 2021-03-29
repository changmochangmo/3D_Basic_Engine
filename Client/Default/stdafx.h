// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <string>
#include <process.h>

//For Grapchis
#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

//Engine's stdafx.h
#include "EngineStdafx.h"

//Engine's includes
#include "ClientTypedef.h"
#include "ClientDefine.h"
#include "ClientEnum.h"
#include "ClientMacro.h"
#include "ClientStructure.h"

// ����
#include <io.h>
#include "fmod.h"
#pragma comment (lib, "fmodex_vc.lib")
