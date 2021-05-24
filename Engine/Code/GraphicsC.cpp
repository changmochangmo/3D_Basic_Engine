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
#include "MeshData.h"

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
	CComponent::InitClone(spClone, pObject);
	spClone->m_renderID = m_renderID;

	return spClone;
}
void CGraphicsC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();

		GET_VALUE(isStatic, dataID, objectKey, L"renderID", m_renderID);
	}
}

void CGraphicsC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_spMesh		= m_pOwner->GetComponent<CMeshC>();
	m_spTexture		= m_pOwner->GetComponent<CTextureC>();
	m_spTransform	= m_pOwner->GetComponent<CTransformC>();
	m_spBitmap		= m_pOwner->GetComponent<CBitmapC>();

	if(m_spMesh != nullptr)
		GenerateBV();

	
	  
	m_mtrl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_mtrl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f);
	m_mtrl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_mtrl.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	m_mtrl.Power = 0.f;
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

	ADD_TO_RENDER_LIST(m_renderID, spGraphicC);
}

void CGraphicsC::OnDestroy(void)
{
}

void CGraphicsC::OnEnable(void)
{
	__super::OnEnable();
}

void CGraphicsC::GenerateBV(void)
{
	_float3 meshSize	= m_spMesh->GetMeshSize();
	_float3 mySize		= m_spTransform->GetSize();

	m_sizeBV.x = meshSize.x * mySize.x;
	m_sizeBV.y = meshSize.y * mySize.y;
	m_sizeBV.z = meshSize.z * mySize.z;

	
	m_offsetBV = (m_spMesh->GetMaxVertex() + m_spMesh->GetMinVertex()) / 2.f;
}


void CGraphicsC::OnDisable(void)
{
}