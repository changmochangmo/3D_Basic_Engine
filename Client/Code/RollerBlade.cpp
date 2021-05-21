#include "stdafx.h"
#include "RollerBlade.h"
#include "DynamicMesh.h"
#include "SceneManager.h"
#include "FRC.h"

_uint CRollerBlade::m_s_uniqueID = 0;

CRollerBlade::CRollerBlade()
{
}


CRollerBlade::~CRollerBlade()
{
	OnDestroy();
}

SP(CRollerBlade) CRollerBlade::Create(_bool isStatic)
{
	SP(CRollerBlade) spInstance(new CRollerBlade, Engine::SmartDeleter<CRollerBlade>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CRollerBlade::MakeClone(void)
{
	SP(CRollerBlade) spClone(new CRollerBlade, Engine::SmartDeleter<CRollerBlade>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	return spClone;
}

void CRollerBlade::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Enemy;
	m_dataID = (_int)EDataID::Enemy;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spCollision = AddComponent<Engine::CCollisionC>();
	m_spRigidBody = AddComponent<Engine::CRigidBodyC>();

	m_spTransform->SetSize(0.5f, 0.5f, 0.5f);
	m_spTransform->SetRotationY(D3DXToRadian(180));
	m_spTransform->SetRotationX(D3DXToRadian(90));
	m_spTransform->SetPosition(11, -25, 3);

	m_spRigidBody->SetUseGravity(false);
}

void CRollerBlade::Start(void)
{
	__super::Start();

	Engine::CDynamicMesh* pBossMeshData =
		static_cast<Engine::CDynamicMesh*>(m_pBoss->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);

	Engine::_DerivedD3DXFRAME*	pFrame;

	AddComponent<Engine::CDebugC>();

	if(m_isRightHand)
		pFrame = pBossMeshData->GetFrameByName("Boss01-R-Hand");
	else
		pFrame = pBossMeshData->GetFrameByName("Boss01-L-Hand");

	m_pParentBoneMatrix = &pFrame->CombinedTransformMatrix;
	m_pParentWorldMatrix = &m_pBoss->GetTransform()->GetWorldMatrix();

	m_pPlayerTransform = Engine::GET_CUR_SCENE->FindObjectWithKey(L"Player")->GetTransform().get();
	//m_spTransform->AddPositionY(2.5f);
}

void CRollerBlade::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CRollerBlade::Update(void)
{
	__super::Update();
	
}

void CRollerBlade::LateUpdate(void)
{
	__super::LateUpdate();
	
	if(m_isOnHand)
		m_spTransform->UpdateParentMatrix(&(*m_pParentBoneMatrix * *m_pParentWorldMatrix));
	else
		static_cast<Engine::CDynamicMesh*>(m_spMesh->GetMeshDatas()[0])->ChangeAniSet(1);

	if (m_isOnHand == false) 
	{
		if (m_spTransform->GetSize().x == 0.5f)
		{
			m_spTransform->SetSize(0.005f, 0.005f, 0.005f);
			_float3 dir;
			if (m_isHoming)
			{
				m_spTransform->SetPosition(m_pBoss->GetTransform()->GetPosition() + UP_VECTOR);
				dir = UP_VECTOR;
				m_isCharging = true;
			}
			else
			{
				m_spTransform->SetPosition(m_pBoss->GetTransform()->GetPosition() + _float3(0, 0.3f, 0) + m_pBoss->GetTransform()->GetForward());
				if (m_spTransform->GetPosition().x > -7.7f)
					dir = _float3(-1, 0, 0);
				else
					dir = _float3(1, 0, 0);
			}
			m_spRigidBody->AddForce(dir * m_speed);
		}
	}

	if (m_isCharging)
	{
		m_chargeTimer += GET_DT;
		if (m_chargeTimer >= m_chargeDuration)
		{
			_float3 dir = m_pPlayerTransform->GetPosition() - m_spTransform->GetPosition();
			m_spRigidBody->SetVelocity(dir);
			m_isCharging = false;
			m_chargeTimer = 0.f;
		}
	}
}

void CRollerBlade::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CRollerBlade::OnEnable(void)
{
	__super::OnEnable();
	
}

void CRollerBlade::OnDisable(void)
{
	__super::OnDisable();
	
}

void CRollerBlade::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CRollerBlade::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	m_isEnabled = false;
	
	m_spTransform->SetSizeX(0.5f);
	m_spTransform->SetPosition(ZERO_VECTOR);
	m_spRigidBody->SetVelocity(ZERO_VECTOR);
}

void CRollerBlade::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CRollerBlade::OnCollisionExit(Engine::_CollisionInfo ci)
{
}
