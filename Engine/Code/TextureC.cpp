#include "EngineStdafx.h"
#include "Object.h"
#include "TextureStore.h"
#include "DataStore.h"

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

	return spClone;
}

void CTextureC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic = m_pOwner->GetIsStatic();
		_int dataID = m_pOwner->GetDataID();
		std::wstring objectKey = m_pOwner->GetObjectKey();

		GET_VALUE(isStatic, dataID, objectKey, L"numOfTex", m_numOfTex);
		for (_int i = 0; i < m_numOfTex; ++i)
		{
			std::wstring texKey;
			GET_VALUE(isStatic, dataID, objectKey, L"textureKey" + std::to_wstring(i), texKey);
			m_vTexData.emplace_back(CTextureStore::GetInstance()->GetTextureData(texKey));
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


void CTextureC::AddTexture(std::wstring const & textureKey)
{
	m_vTexData.emplace_back(CTextureStore::GetInstance()->GetTextureData(textureKey));
}

void CTextureC::ChangeTexture(const _size index, std::wstring const & textureKey)
{
	_size size = m_vTexData.size();
	if (size == index)
		m_vTexData.push_back(CTextureStore::GetInstance()->GetTextureData(textureKey));
	else if (size < index)
	{
		MSG_BOX(__FILE__, L"index is broken in ChangeTexture");
		ABORT;
	}
	else
		m_vTexData[index] = CTextureStore::GetInstance()->GetTextureData(textureKey);
}
