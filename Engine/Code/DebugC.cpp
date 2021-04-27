#include "EngineStdafx.h"
#include "DebugC.h"
#include "BoundingVolume.h"
#include "DataStore.h"
#include "ObjectFactory.h"

USING(Engine)
CDebugC::CDebugC(void)
{
}

CDebugC::~CDebugC(void)
{
}

SP(CComponent) CDebugC::MakeClone(CObject * pObject)
{
	SP(CDebugC) spClone(new CDebugC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CDebugC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();

		std::wstring debugMeshKey;
		GET_VALUE(isStatic, dataID, objectKey, L"debugMeshKey", debugMeshKey);
	}
}

void CDebugC::Start(SP(CComponent) spThis)
{
	m_spBV = std::dynamic_pointer_cast<CBoundingVolume>(ADD_CLONE(L"BoundingVolume", true));
	m_spBV->SetOwner(m_pOwner);
}

void CDebugC::FixedUpdate(SP(CComponent) spThis)
{
}

void CDebugC::Update(SP(CComponent) spThis)
{
}

void CDebugC::LateUpdate(SP(CComponent) spThis)
{
}

void CDebugC::OnDestroy(void)
{
	m_spBV->SetDeleteThis(true);
	m_spBV.reset();
}

void CDebugC::OnEnable(void)
{
	m_spBV->OnEnable();
}

void CDebugC::OnDisable(void)
{
	m_spBV->OnDisable();
}
