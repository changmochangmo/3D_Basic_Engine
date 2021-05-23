#include "stdafx.h"
#include "JumpHat.h"
#include "DynamicMesh.h"
#include "SceneManager.h"
#include "FRC.h"
#include "Player.h"


_uint CJumpHat::m_s_uniqueID = 0;

CJumpHat::CJumpHat()
{
}


CJumpHat::~CJumpHat()
{
	OnDestroy();
}

SP(CJumpHat) CJumpHat::Create(_bool isStatic)
{
	SP(CJumpHat) spInstance(new CJumpHat, Engine::SmartDeleter<CJumpHat>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CJumpHat::MakeClone(void)
{
	SP(CJumpHat) spClone(new CJumpHat, Engine::SmartDeleter<CJumpHat>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();

	return spClone;
}

void CJumpHat::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Player;
	m_dataID = (_int)EDataID::Scene;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();


	m_spTransform->SetRotationZ(D3DXToRadian(-70));
	m_spTransform->SetRotationY(D3DXToRadian(-90));
	//m_spTransform->SetRotationY(-PI / 2.f);
	////m_spTransform->SetRotationX(D3DXToRadian(90));
	m_spTransform->SetPosition(9, 10, 0);
	m_spTransform->SetSize(.6f, .6f, .6f);
}

void CJumpHat::Start(void)
{
	__super::Start();
	Engine::CDynamicMesh* pPlayerMeshData =
		static_cast<Engine::CDynamicMesh*>(m_pPlayer->GetComponent<Engine::CMeshC>()->GetMeshDatas()[1]);

	Engine::_DerivedD3DXFRAME*	pFrame;

	pFrame = pPlayerMeshData->GetFrameByName("bip_hat01");


	m_pParentBoneMatrix = &pFrame->CombinedTransformMatrix;
	m_pParentWorldMatrix = &m_pPlayer->GetTransform()->GetWorldMatrix();

}

void CJumpHat::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CJumpHat::Update(void)
{
	__super::Update();
	
}

void CJumpHat::LateUpdate(void)
{
	__super::LateUpdate();
	m_spTransform->UpdateParentMatrix(&(*m_pParentBoneMatrix * *m_pParentWorldMatrix));

	_float3 fuck = m_spTransform->GetPosition();
}

void CJumpHat::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CJumpHat::OnEnable(void)
{
	__super::OnEnable();
	
}

void CJumpHat::OnDisable(void)
{
	__super::OnDisable();
	
}

void CJumpHat::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

