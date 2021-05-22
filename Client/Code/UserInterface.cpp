#include "stdafx.h"
#include "UserInterface.h"
#include "DataStore.h"


_uint CUserInterface::m_s_uniqueID = 0;

CUserInterface::CUserInterface()
{
}


CUserInterface::~CUserInterface()
{
}

SP(CUserInterface) CUserInterface::Create(std::wstring objectKey)
{
	SP(CUserInterface) spUIObject(new CUserInterface, Engine::SmartDeleter<CUserInterface>);
	spUIObject->SetIsStatic(false);
	spUIObject->SetObjectKey(objectKey);
	spUIObject->Awake();


	return spUIObject;
}

SP(Engine::CObject) CUserInterface::MakeClone(void)
{
	SP(CUserInterface) spClone(new CUserInterface, Engine::SmartDeleter<CUserInterface>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spBitmap		= spClone->GetComponent<Engine::CBitmapC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();

	spClone->m_objectKey	= m_objectKey;

	return spClone;
}

void CUserInterface::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;
	m_dataID = (_int)EDataID::UI;

	m_spBitmap		= AddComponent<Engine::CBitmapC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();

	//m_spGraphics->SetRenderID((_int)Engine::ERenderID::UI);
}

void CUserInterface::Start(void)
{
	__super::Start();
	
	_int dataID = GetDataID();

	_float3 pos;
	Engine::GET_VALUE(false, dataID, m_objectKey, L"position", pos);

	_float3 size;
	Engine::GET_VALUE(false, dataID, m_objectKey, L"size", size);

	if(pos != ZERO_VECTOR)
		m_spTransform->SetPosition(pos);
	if(size != ZERO_VECTOR)
		m_spTransform->SetSize(size);
}

void CUserInterface::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CUserInterface::Update(void)
{
	__super::Update();
	
}

void CUserInterface::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CUserInterface::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CUserInterface::OnEnable(void)
{
	__super::OnEnable();
	
}

void CUserInterface::OnDisable(void)
{
	__super::OnDisable();
	
}

void CUserInterface::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
