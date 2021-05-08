#include "EngineStdafx.h"
#include "Grid.h"

USING(Engine)
_uint CGrid::m_s_uniqueID = 0;
CGrid::CGrid()
{
}


CGrid::~CGrid()
{
}

SP(CGrid) CGrid::Create(_bool isStatic)
{
	SP(CGrid) spInstance(new CGrid, SmartDeleter<CGrid>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGrid::MakeClone(void)
{
	SP(CGrid) spClone(new CGrid, SmartDeleter<CGrid>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<CGraphicsC>();

	return spClone;
}

void CGrid::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Grid;
	m_dataID	= (_int)EDataID::Grid;

	m_spMesh		= AddComponent<CMeshC>();
	m_spGraphics	= AddComponent<CGraphicsC>();
}

void CGrid::Start(void)
{
	__super::Start();
}

void CGrid::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CGrid::Update(void)
{
	__super::Update();
}

void CGrid::LateUpdate(void)
{
	__super::LateUpdate();
}

void CGrid::OnDestroy(void)
{
	__super::OnDestroy();
}

void CGrid::OnEnable(void)
{
	__super::OnEnable();
}

void CGrid::OnDisable(void)
{
	__super::OnDisable();
}

void CGrid::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
