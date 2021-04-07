#include "EngineStdafx.h"
#include "Collider.h"


USING(Engine)
CCollider::CCollider(void)
{
}

CCollider::~CCollider(void)
{
}

void CCollider::Free(void)
{
	delete this;
}

void CCollider::Awake(void)
{
	__super::Awake();
	MakeBS();
}

