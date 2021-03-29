#include "EngineStdafx.h"
#include "GraphicsComponent.h"
#include "DeviceManager.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Shader.h"
#include "WndApp.h"

USING(Engine)
CGraphicsComponent::CGraphicsComponent(void)  
{
}

CGraphicsComponent::~CGraphicsComponent(void)
{
}

SHARED(CComponent) CGraphicsComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CGraphicsComponent) pClone(new CGraphicsComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetRenderID(m_renderID);

	return pClone;
}
void CGraphicsComponent::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;
}

void CGraphicsComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_pMesh			= m_pOwner->GetComponent<CMeshComponent>();
	m_pTexture		= m_pOwner->GetComponent<CTextureComponent>();
	m_pTransform	= m_pOwner->GetComponent<CTransformComponent>();

	if (m_pBitmap = m_pOwner->GetComponent<CBitmapComponent>())
		m_renderID = ERenderID::UI;
}

_uint CGraphicsComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CGraphicsComponent::Update(SHARED(CComponent) spThis /* Shared pointer of current component*/)
{
	return _uint();
}

_uint CGraphicsComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CGraphicsManager::GetInstance()->
		AddToRenderList(m_renderID, std::dynamic_pointer_cast<CGraphicsComponent>(spThis));
	return NO_EVENT;
}

_uint CGraphicsComponent::PreRender(void)
{
	if (m_pTexture != nullptr)
	{
		GET_DEVICE->SetTexture(0, m_pTexture->GetTexData()->pTexture);
	}
	else
		GET_DEVICE->SetTexture(0, nullptr);

	
	if (m_pMesh != nullptr)
	{
		GET_DEVICE->SetStreamSource(0, m_pMesh->GetMeshData()->vertexBuffer, 0, m_pMesh->GetMeshData()->vertexSize);
		GET_DEVICE->SetFVF(m_pMesh->GetMeshData()->FVF);
		GET_DEVICE->SetIndices(m_pMesh->GetMeshData()->indexBuffer);

		CShader* pShader = CShaderManager::GetInstance()->GetShader(L"TextureShader");
		pShader->PreRender(this);
	}
	else if (m_pBitmap != nullptr)
	{
		GET_DEVICE->SetStreamSource(0, m_pBitmap->GetVertexBuffer(), 0, sizeof(_CustomVertex2D));
		GET_DEVICE->SetIndices(m_pBitmap->GetIndexBuffer());
		GET_DEVICE->SetFVF(customFVF2D);
	}
	


	return NO_EVENT;
}

_uint CGraphicsComponent::Render(void)
{
	if (m_pMesh != nullptr)
	{
		CShader* pShader = CShaderManager::GetInstance()->GetShader(L"TextureShader");
		pShader->Render(this);
	}
	else if (m_pBitmap != nullptr)
	{
		//D3DXMATRIX persMatView;
		//D3DXMATRIX persMatProj;
		//
		//GET_DEVICE->GetTransform(D3DTS_VIEW, &persMatView);
		//GET_DEVICE->GetTransform(D3DTS_PROJECTION, &persMatProj);
		//
		//D3DXMATRIX s_orthoMatView;
		//D3DXMATRIX s_orthoMatProj;
		//
		//D3DXVECTOR3 oCamPos = D3DXVECTOR3(0, 0, GET_MAIN_CAM->GetTransform()->GetPosition().z);
		//D3DXVECTOR3 oCamTar = D3DXVECTOR3(0, 0, GET_MAIN_CAM->GetAt().z);
		//
		//D3DXVECTOR3 pos = GET_MAIN_CAM->GetTransform()->GetPosition();
		//D3DXVECTOR3 targ = GET_MAIN_CAM->GetAt();
		//D3DXVECTOR3 up = GET_MAIN_CAM->GetUp();
		//
		//D3DXMatrixLookAtLH(&s_orthoMatView, &pos, &targ, &up);
		//D3DXMatrixOrthoLH(&s_orthoMatProj,
		//	FLOAT(GET_WND_WIDTH), FLOAT(GET_WND_HEIGHT),
		//	FLOAT(GET_MAIN_CAM->GetNear()), FLOAT(GET_MAIN_CAM->GetFar()));
		//
		//GET_DEVICE->SetTransform(D3DTS_VIEW, &s_orthoMatView);
		//GET_DEVICE->SetTransform(D3DTS_PROJECTION, &s_orthoMatProj);
		//GET_DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
		//
		//GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		//
		//GET_DEVICE->SetTransform(D3DTS_VIEW, &persMatView);
		//GET_DEVICE->SetTransform(D3DTS_PROJECTION, &persMatProj);
	}

	return _uint();
}

_uint CGraphicsComponent::PostRender(void)
{
	return _uint();
}

void CGraphicsComponent::OnDestroy(void)
{
}

void CGraphicsComponent::OnEnable(void)
{
	__super::OnEnable();
}


void CGraphicsComponent::OnDisable(void)
{
}