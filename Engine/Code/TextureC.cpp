#include "EngineStdafx.h"
#include "GameObject.h"
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

SP(CComponent) CTextureC::MakeClone(CGameObject* pObject)
{
	SP(CTextureC) spClone(new CTextureC);
	__super::InitClone(spClone, pObject);

	spClone->SetTextureKey(m_textureKey);
	spClone->SetTexData(m_pTexData);
	spClone->SetColor(m_color);

	return spClone;
}

void CTextureC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
}


void CTextureC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	//현재 오브젝트가 Static Scene의 오브젝트냐?
	_bool isStatic	= m_pOwner->GetIsStatic();

	//현재 오브젝트의 Layer / Object 키 값
	_int ownerDataID = m_pOwner->GetDataID();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	GET_VALUE(isStatic, ownerDataID, objectKey, L"textureKey", m_textureKey);


	if ((m_pTexData = CTextureStore::GetInstance()->GetTextureData(m_textureKey)) == nullptr)
		m_pTexData = CTextureStore::GetInstance()->GetTextureData(L"None");
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
