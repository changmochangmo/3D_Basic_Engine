#include "EngineStdafx.h"
#include "DebugC.h"
#include "DataStore.h"
#include "ObjectFactory.h"

#include "BoundingVolume.h"
#include "DebugCollider.h"


USING(Engine)
CDebugC::CDebugC(void)
{
}

CDebugC::~CDebugC(void)
{
	OnDestroy();
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
}

void CDebugC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	//if (m_pOwner->GetComponent<CMeshC>() != nullptr)
	//{
	//	m_spBV = std::dynamic_pointer_cast<CBoundingVolume>(ADD_CLONE(L"BoundingVolume", true));
	//	m_spBV->SetOwner(m_pOwner);
	//}

	SP(CCollisionC) spOwnerCC = m_pOwner->GetComponent<CCollisionC>();
	if (spOwnerCC != nullptr)
	{
		m_vDebugCollider.resize(spOwnerCC->GetColliders().size());
		const std::vector<CCollider*>& vOwnerColliders = spOwnerCC->GetColliders();
		for (_size i = 0; i < m_vDebugCollider.size(); ++i)
		{
			m_vDebugCollider[i] = std::dynamic_pointer_cast<CDebugCollider>(ADD_CLONE(L"DebugCollider", true));
			m_vDebugCollider[i]->SetOwner(m_pOwner);
			m_vDebugCollider[i]->SetCollider(vOwnerColliders[i]);
		}
	}
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
	if (m_spBV != nullptr)
	{
		m_spBV->SetDeleteThis(true);
		m_spBV.reset();
	}

	for (auto& debugCollider : m_vDebugCollider)
	{
		debugCollider->SetDeleteThis(true);
		debugCollider.reset();
	}

	m_vDebugCollider.clear();
}

void CDebugC::OnEnable(void)
{
	m_spBV->OnEnable();
}

void CDebugC::OnDisable(void)
{
	m_spBV->OnDisable();
}

void CDebugC::AddDebugCollider(CCollider* pCollider)
{
	SP(CDebugCollider) spDC = std::dynamic_pointer_cast<CDebugCollider>(ADD_CLONE(L"DebugCollider", true));
	spDC->SetOwner(m_pOwner);
	spDC->SetCollider(pCollider);
	m_vDebugCollider.emplace_back(spDC);
}
