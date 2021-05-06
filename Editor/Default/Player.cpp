#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "FRC.h"
#include "DynamicMesh.h"
#include "MeshData.h"

_uint CPlayer::m_s_uniqueID = 0;

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

SP(CPlayer) CPlayer::Create(_bool isStatic)
{
	SP(CPlayer) spInstance(new CPlayer, Engine::SmartDeleter<CPlayer>);
	spInstance->SetIsStatic(isStatic);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPlayer::MakeClone(void)
{
	SP(CPlayer) spClone(new CPlayer, Engine::SmartDeleter<CPlayer>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	return spClone;
}

//���� ������Ÿ�Ը� �����ũ�� Ÿ��, Ŭ���� �����ũ�� �� ������Ÿ���� �����ذ�.
void CPlayer::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Player;
	m_dataID	= (_int)EDataID::Player;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
}

void CPlayer::Start(void)
{
	__super::Start();
}

void CPlayer::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CPlayer::Update(void)
{
	__super::Update();

	if (Engine::IMKEY_PRESS(KEY_RIGHT))
	{
		m_spTransform->MoveRight(3 * GET_DT);

	}
	if (Engine::IMKEY_PRESS(KEY_LEFT))
	{
		m_spTransform->MoveLeft(3 * GET_DT);
	}
	if (Engine::IMKEY_PRESS(KEY_UP))
	{
		m_spTransform->MoveForward(3 * GET_DT);
	}
	if (Engine::IMKEY_PRESS(KEY_DOWN))
	{
		m_spTransform->MoveBackward(3 * GET_DT);
	}

	const std::vector<Engine::CMeshData*>& vMeshData = m_spMesh->GetMeshDatas();
	if (Engine::IMKEY_PRESS(KEY_1))
	{
		for (_int i = 0; i < (_int)vMeshData.size(); ++i)
			dynamic_cast<Engine::CDynamicMesh*>(vMeshData[i])->PlayAnimation();
	}
	if (Engine::IMKEY_DOWN(KEY_2))
	{
		static int aniIndex = 0;
		for (_int i = 0; i < (_int)vMeshData.size(); ++i)
			dynamic_cast<Engine::CDynamicMesh*>(vMeshData[i])->ChangeAniSet(aniIndex++);
	}

	if (Engine::IMKEY_PRESS(KEY_4))
	{
		for (_int i = 0; i < (_int)vMeshData.size(); ++i)
		{
			Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[i]);

			pDM->PlayAnimation();

			if (pDM->IsAnimationEnd())
				pDM->ChangeAniSet(pDM->GetAniCtrl()->GetCurIndex() + 1);
		}
	}
	if (Engine::IMKEY_DOWN(KEY_F2))
	{
		for (_int i = 0; i < (_int)vMeshData.size(); ++i)
		{
			Engine::CDynamicMesh* pDM = dynamic_cast<Engine::CDynamicMesh*>(vMeshData[i]);
			pDM->ChangeAniSet("Stand_Idle");
		}
	}
}

void CPlayer::LateUpdate(void)
{
	__super::LateUpdate();
}

void CPlayer::OnDestroy(void)
{
	__super::OnDestroy();
}

void CPlayer::OnEnable(void)
{
	__super::OnEnable();
}

void CPlayer::OnDisable(void)
{
	__super::OnDisable();
}

void CPlayer::OnCollisionEnter(Engine::_CollisionInfo ci)
{
}

void CPlayer::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CPlayer::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CPlayer::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
