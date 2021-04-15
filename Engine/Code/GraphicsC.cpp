#include "EngineStdafx.h"

#include "DeviceManager.h"
#include "GraphicsManager.h"

#include "ShaderManager.h"
#include "Shader.h"

#include "SceneManager.h"
#include "Scene.h"

#include "WndApp.h"
#include "DataStore.h"

#include "Object.h"

USING(Engine)
CGraphicsC::CGraphicsC(void)  
{
}

CGraphicsC::~CGraphicsC(void)
{
	OnDestroy();
}

SP(CComponent) CGraphicsC::MakeClone(CObject* pObject)
{
	SP(CGraphicsC) spClone(new CGraphicsC);
	__super::InitClone(spClone, pObject);

	spClone->SetRenderID(m_renderID);

	return spClone;
}
void CGraphicsC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic = m_pOwner->GetIsStatic();
		_int dataID = m_pOwner->GetDataID();
		std::wstring objectKey = m_pOwner->GetObjectKey();

		GET_VALUE(isStatic, dataID, objectKey, L"renderID", m_renderID);
	}
}

void CGraphicsC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_pMesh			= m_pOwner->GetComponent<CMeshC>();
	m_pTexture		= m_pOwner->GetComponent<CTextureC>();
	m_pTransform	= m_pOwner->GetComponent<CTransformC>();
}

void CGraphicsC::FixedUpdate(SP(CComponent) spThis)
{
}

void CGraphicsC::Update(SP(CComponent) spThis)
{
}

void CGraphicsC::LateUpdate(SP(CComponent) spThis)
{
	CGraphicsManager::GetInstance()->
		AddToRenderList(m_renderID, std::dynamic_pointer_cast<CGraphicsC>(spThis));
}

void CGraphicsC::PreRender(void)
{	
	CShader* pShader = CShaderManager::GetInstance()->GetShader(L"TextureShader");
	pShader->PreRender(this);
}

void CGraphicsC::Render(void)
{
	CShader* pShader = CShaderManager::GetInstance()->GetShader(L"TextureShader");
	pShader->Render(this);
}

void CGraphicsC::PostRender(void)
{
	CShader* pShader = CShaderManager::GetInstance()->GetShader(L"TextureShader");
	pShader->PostRender(this);
}

void CGraphicsC::OnDestroy(void)
{
}

void CGraphicsC::OnEnable(void)
{
	__super::OnEnable();
}


void CGraphicsC::OnDisable(void)
{
}