#include "stdafx.h"
#include "FireHat.h"
#include "DynamicMesh.h"
#include "SceneManager.h"
#include "FRC.h"
#include "Player.h"


_uint CFireHat::m_s_uniqueID = 0;

CFireHat::CFireHat()
{
}


CFireHat::~CFireHat()
{
	OnDestroy();
}

SP(CFireHat) CFireHat::Create(_bool isStatic)
{
	SP(CFireHat) spInstance(new CFireHat, Engine::SmartDeleter<CFireHat>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CFireHat::MakeClone(void)
{
	SP(CFireHat) spClone(new CFireHat, Engine::SmartDeleter<CFireHat>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();

	return spClone;
}

void CFireHat::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Player;
	m_dataID = (_int)EDataID::Scene;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();


	m_spTransform->SetRotationZ(-PI / 2.f);
	//m_spTransform->SetRotationY(-PI / 2.f);
	////m_spTransform->SetRotationX(D3DXToRadian(90));
	m_spTransform->SetPosition(35, 0, 0);
	//m_spTransform->SetSize(1.2f, 1.2f, 1.2f);
}

void CFireHat::Start(void)
{
	__super::Start();
	Engine::CDynamicMesh* pPlayerMeshData =
		static_cast<Engine::CDynamicMesh*>(m_pPlayer->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);

	Engine::_DerivedD3DXFRAME*	pFrame;

	pFrame = pPlayerMeshData->GetFrameByName("bip_neck");


	m_pParentBoneMatrix = &pFrame->CombinedTransformMatrix;
	m_pParentWorldMatrix = &m_pPlayer->GetTransform()->GetWorldMatrix();

}

void CFireHat::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CFireHat::Update(void)
{
	__super::Update();

}

void CFireHat::LateUpdate(void)
{
	__super::LateUpdate();
	m_spTransform->UpdateParentMatrix(&(*m_pParentBoneMatrix * *m_pParentWorldMatrix));

	_float3 fuck = m_spTransform->GetPosition();
}

void CFireHat::OnDestroy(void)
{
	__super::OnDestroy();

}

void CFireHat::OnEnable(void)
{
	__super::OnEnable();

}

void CFireHat::OnDisable(void)
{
	__super::OnDisable();

}

void CFireHat::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

