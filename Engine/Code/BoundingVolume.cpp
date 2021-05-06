#include "EngineStdafx.h"
#include "BoundingVolume.h"
#include "Object.h"
#include "MeshData.h"

USING(Engine)
_uint CBoundingVolume::m_s_uniqueID = 0;

CBoundingVolume::CBoundingVolume()
{
}


CBoundingVolume::~CBoundingVolume()
{
}

SP(CBoundingVolume) CBoundingVolume::Create(_bool isStatic)
{
	SP(CBoundingVolume) spInstance(new CBoundingVolume, Engine::SmartDeleter<CBoundingVolume>);
	spInstance->SetIsStatic(true);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBoundingVolume::MakeClone(void)
{
	SP(CBoundingVolume) spClone(new CBoundingVolume, Engine::SmartDeleter<CBoundingVolume>);
	CObject::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	return spClone;
}

void CBoundingVolume::Awake(void)
{
	__super::Awake();
	m_layerID	= (_int)ELayerID::BV;
}

void CBoundingVolume::Start(void)
{
	__super::Start();
	SP(CGraphicsC) spOwnerGraphics = m_pOwner->GetComponent<CGraphicsC>();

	m_offset = spOwnerGraphics->GetOffsetBV();
	m_spTransform->SetSize(spOwnerGraphics->GetSizeBV());
}

void CBoundingVolume::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBoundingVolume::Update(void)
{
	__super::Update();
}

void CBoundingVolume::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBoundingVolume::OnDestroy(void)
{
	__super::OnDestroy();
}

void CBoundingVolume::OnEnable(void)
{
	__super::OnEnable();
}

void CBoundingVolume::OnDisable(void)
{
	__super::OnDisable();
}

void CBoundingVolume::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
