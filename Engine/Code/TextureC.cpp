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

	//spClone->SetTextureKey(m_textureKey);
	spClone->SetTexData(m_ppTexData);
	spClone->SetColor(m_color);

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
		m_ppTexData = new _TexData*[m_numOfTex];
		for (_int i = 0; i < m_numOfTex; ++i)
		{
			std::wstring texKey;
			GET_VALUE(isStatic, dataID, objectKey, L"textureKey" + std::to_wstring(i), texKey);
			m_ppTexData[i] = CTextureStore::GetInstance()->GetTextureData(texKey);
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

void CTextureC::InitTextureBuffer(const int numOfTex)
{
	if(m_ppTexData == nullptr)
		m_ppTexData = new _TexData*[numOfTex];
	else
	{
		MSG_BOX(__FILE__, L"TexData is already allocated");
		ABORT;
	}
}

void CTextureC::ChangeTexture(const int index, std::wstring const & textureKey)
{
	if (m_ppTexData == nullptr)
		InitTextureBuffer(index + 1);

	m_ppTexData[index] = CTextureStore::GetInstance()->GetTextureData(textureKey);
}
