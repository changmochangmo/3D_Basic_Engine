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
	}
}

void CGraphicsC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_spMesh		= m_pOwner->GetComponent<CMeshC>();
	m_spTexture		= m_pOwner->GetComponent<CTextureC>();
	m_spTransform	= m_pOwner->GetComponent<CTransformC>();
	m_spDebug		= m_pOwner->GetComponent<CDebugC>();
}

void CGraphicsC::FixedUpdate(SP(CComponent) spThis)
{
}

void CGraphicsC::Update(SP(CComponent) spThis)
{
}

void CGraphicsC::LateUpdate(SP(CComponent) spThis)
{
	SP(CGraphicsC) spGraphicC = std::dynamic_pointer_cast<CGraphicsC>(spThis);

	if (m_spMesh)
		ADD_TO_RENDER_LIST(m_spMesh->GetRenderID(), spGraphicC);
	if (m_spDebug)
		ADD_TO_RENDER_LIST(m_spDebug->GetRenderID(), spGraphicC);
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