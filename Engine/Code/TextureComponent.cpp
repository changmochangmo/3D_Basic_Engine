#include "EngineStdafx.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "TextureStore.h"
#include "DataStore.h"

USING(Engine)
CTextureComponent::CTextureComponent()  
{
}


CTextureComponent::~CTextureComponent(void)
{
}

SHARED(CComponent) CTextureComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CTextureComponent) spClone(new CTextureComponent);
	__super::InitClone(spClone, pObject);

	spClone->SetTextureKey(m_textureKey);
	spClone->SetTexData(m_pTexData);
	spClone->SetColor(m_color);

	return spClone;
}

void CTextureComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
}


void CTextureComponent::Start(SHARED(CComponent) spThis)
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

_uint CTextureComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CTextureComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CTextureComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}



void CTextureComponent::OnDestroy(void)
{
}

void CTextureComponent::OnEnable(void)
{
}

void CTextureComponent::OnDisable(void)
{
}
