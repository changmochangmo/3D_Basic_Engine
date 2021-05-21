#include "stdafx.h"
#include "Decoration.h"
#include "DynamicMesh.h"

_uint CDecoration::m_s_uniqueID = 0;
CDecoration::CDecoration()
{
}


CDecoration::~CDecoration()
{
}

SP(CDecoration) CDecoration::Create(_bool isStatic)
{
	SP(CDecoration) spInstance(new CDecoration, Engine::SmartDeleter<CDecoration>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetAddExtra(true);
	spInstance->Awake();
	

	return spInstance;
}

SP(Engine::CObject) CDecoration::MakeClone(void)
{
	SP(CDecoration) spClone(new CDecoration, Engine::SmartDeleter<CDecoration>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	

	spClone->m_vAnimationIndices = m_vAnimationIndices;
	return spClone;
}

void CDecoration::Awake(void)
{
	__super::Awake();
	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
}

void CDecoration::Start(void)
{
	__super::Start();
	m_spMesh		= GetComponent<Engine::CMeshC>();
	m_spTexture		= GetComponent<Engine::CTextureC>();
	m_spGraphics	= GetComponent<Engine::CGraphicsC>();

	for (auto& meshData : m_spMesh->GetMeshDatas())
	{
		if (meshData->GetMeshType() == (_int)Engine::EMeshType::Dynamic)
		{
			Engine::CDynamicMesh* pDM = static_cast<Engine::CDynamicMesh*>(meshData);
			pDM->ChangeAniSet(m_vAnimationIndices[m_aniIndex]);
		}
	}
}

void CDecoration::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CDecoration::Update(void)
{
	__super::Update();

	_int curAniIndex = m_aniIndex;
	for (auto& meshData : m_spMesh->GetMeshDatas())
	{
		Engine::CDynamicMesh* pDM = static_cast<Engine::CDynamicMesh*>(meshData);
		if (pDM->IsAnimationEnd())
		{
			curAniIndex = m_aniIndex + 1;
			if (curAniIndex == m_vAnimationIndices.size())
				curAniIndex = 0;
			pDM->ChangeAniSet(m_vAnimationIndices[curAniIndex]);
		}
	}
	m_aniIndex = curAniIndex;
}

void CDecoration::LateUpdate(void)
{
	__super::LateUpdate();
}

void CDecoration::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDecoration::OnEnable(void)
{
	__super::OnEnable();
}

void CDecoration::OnDisable(void)
{
	__super::OnDisable();
}

void CDecoration::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CDecoration::AddAnimationIndex(_int index)
{
	m_vAnimationIndices.emplace_back(index);
}
