#include "EngineStdafx.h"
#include "Engine.h"


USING(Engine)
CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::Awake(void)
{
	m_objectKey = GetCurClassName(this);
}
