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
	//else if (m_pBitmap != nullptr)
	//{
	//	GET_DEVICE->SetStreamSource(0, m_pBitmap->GetVertexBuffer(), 0, sizeof(_CustomVertex2D));
	//	GET_DEVICE->SetIndices(m_pBitmap->GetIndexBuffer());
	//	GET_DEVICE->SetFVF(customFVF2D);
	//}
}

void CGraphicsC::Render(void)
{
	if (m_pMesh != nullptr)
	{
		CShader* pShader = CShaderManager::GetInstance()->GetShader(L"TextureShader");
		pShader->Render(this);
	}
	/*else if (m_pBitmap != nullptr)
	{
		D3DXMATRIX persMatView;
		D3DXMATRIX persMatProj;
		
		GET_DEVICE->GetTransform(D3DTS_VIEW, &persMatView);
		GET_DEVICE->GetTransform(D3DTS_PROJECTION, &persMatProj);
		
		D3DXMATRIX s_orthoMatView;
		D3DXMATRIX s_orthoMatProj;
		
		D3DXVECTOR3 oCamPos = D3DXVECTOR3(0, 0, GET_MAIN_CAM->GetTransform()->GetPosition().z);
		D3DXVECTOR3 oCamTar = D3DXVECTOR3(0, 0, GET_MAIN_CAM->GetAt().z);
		
		D3DXVECTOR3 pos = GET_MAIN_CAM->GetTransform()->GetPosition();
		D3DXVECTOR3 targ = GET_MAIN_CAM->GetAt();
		D3DXVECTOR3 up = GET_MAIN_CAM->GetUp();
		
		D3DXMatrixLookAtLH(&s_orthoMatView, &pos, &targ, &up);
		D3DXMatrixOrthoLH(&s_orthoMatProj,
			FLOAT(GET_WND_WIDTH), FLOAT(GET_WND_HEIGHT),
			FLOAT(GET_MAIN_CAM->GetNear()), FLOAT(GET_MAIN_CAM->GetFar()));
		
		GET_DEVICE->SetTransform(D3DTS_VIEW, &s_orthoMatView);
		GET_DEVICE->SetTransform(D3DTS_PROJECTION, &s_orthoMatProj);
		GET_DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
		
		GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		
		GET_DEVICE->SetTransform(D3DTS_VIEW, &persMatView);
		GET_DEVICE->SetTransform(D3DTS_PROJECTION, &persMatProj);
	}*/

}

void CGraphicsC::PostRender(void)
{
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