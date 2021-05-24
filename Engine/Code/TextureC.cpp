#include "EngineStdafx.h"
#include "Object.h"
#include "TextureStore.h"
#include "DataStore.h"
#include "FRC.h"
USING(Engine)
CTextureC::CTextureC()  
{
}


CTextureC::~CTextureC(void)
{
	OnDestroy();
}

SP(CComponent) CTextureC::MakeClone(CObject* pObject)
{
	SP(CTextureC) spClone(new CTextureC);
	__super::InitClone(spClone, pObject);

	spClone->m_vTexData = m_vTexData;
	spClone->m_color	= m_color;
	spClone->m_changeTex = m_changeTex;

	return spClone;
}

void CTextureC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();

		_int numOfTexSet;
		GET_VALUE(isStatic, dataID, objectKey, L"numOfMeshData", numOfTexSet);

		m_vTexData.resize(numOfTexSet);
		for (_int i = 0; i < numOfTexSet; ++i)
		{
			_int numOfTex;
			GET_VALUE(isStatic, dataID, objectKey, L"numOfTex_Set" + std::to_wstring(i), numOfTex);
			m_numOfTex += numOfTex;
			for (_int j = 0; j < numOfTex; ++j)
			{
				std::wstring texKey = L"textureKey" + std::to_wstring(i) + L'_' + std::to_wstring(j);
				GET_VALUE(isStatic, dataID, objectKey, texKey, texKey);
				m_vTexData[i].emplace_back(CTextureStore::GetInstance()->GetTextureData(texKey));
			}
		}
	}
}


void CTextureC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CTextureC::FixedUpdate(SP(CComponent) spThis)
{
}

void CTextureC::Update(SP(CComponent) spThis)
{
	if (m_changeTex)
	{
		m_changeTimer += GET_DT;
		if (m_changeTimer > m_changeDuration)
		{
			m_texIndex++;
			if (m_vTexData[m_meshIndex].size() == m_texIndex)
				m_texIndex = 0;

			m_changeTimer = 0.f;
		}
	}
}

void CTextureC::LateUpdate(SP(CComponent) spThis)
{
}



void CTextureC::OnDestroy(void)
{
}

void CTextureC::OnEnable(void)
{
}

void CTextureC::OnDisable(void)
{
}

void CTextureC::SetAlpha(_float alpha)
{
	m_color.a = alpha;
}

void CTextureC::AddAlpha(_float alpha)
{
	m_color.a += alpha;
}


void CTextureC::AddTexture(std::wstring const & textureKey, _int index)
{
	_size numOfMesh = m_pOwner->GetComponent<CMeshC>()->GetMeshDatas().size();
	if(m_vTexData.size() != numOfMesh)
		m_vTexData.resize(numOfMesh);


	if(index < 0 || index >= numOfMesh)
	{
		MSG_BOX(__FILE__, L"index is broken in AddTexture");
		ABORT;
	}

	m_vTexData[index].emplace_back(CTextureStore::GetInstance()->GetTextureData(textureKey));
}
