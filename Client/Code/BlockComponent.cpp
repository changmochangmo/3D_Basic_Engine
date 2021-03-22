#include "stdafx.h"
#include "..\Header\BlockComponent.h"


CBlockComponent::CBlockComponent()
{
}


CBlockComponent::~CBlockComponent()
{
}

void CBlockComponent::Awake(void)
{
	__super::Awake();
}

void CBlockComponent::Start(SHARED(Engine::CComponent) spThis)
{
	__super::Start(spThis);
}
