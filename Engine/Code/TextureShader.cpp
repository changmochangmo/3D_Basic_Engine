#include "EngineStdafx.h"
#include "TextureShader.h"
#include "DeviceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"
#include "CameraC.h"
#include "Mesh.h"
#include "StaticMesh.h"

USING(Engine)
CTextureShader::CTextureShader()
{
}

CTextureShader::~CTextureShader()
{
}

CTextureShader * CTextureShader::Create(void)
{
	CTextureShader* pTextureShader = new CTextureShader;
	pTextureShader->Awake();
	pTextureShader->Start();

	return pTextureShader;
}

void CTextureShader::Awake(void)
{
	__super::Awake();
	m_filePath = L"..\\..\\Resource\\Shader\\TextureShader.fx";
	
}

void CTextureShader::Start(void)
{
	LoadShader();
}

void CTextureShader::PreRender(CGraphicsC* pGC)
{
	m_pShader->SetMatrix("WorldMatrix", &pGC->GetTransform()->GetWorldMatrix());
	m_pShader->SetMatrix("ViewMatrix", &GET_MAIN_CAM->GetViewMatrix());
	m_pShader->SetMatrix("ProjMatrix", &GET_MAIN_CAM->GetProjMatrix());
	m_pShader->SetVector("Color", &pGC->GetTexture()->GetColor());
}

void CTextureShader::Render(CGraphicsC* pGC)
{
	_uint inumPasses = 0;

	if (SUCCEEDED(m_pShader->Begin(&inumPasses, NULL)))
	{
		for (_uint i = 0; i < inumPasses; ++i)
		{
			if (FAILED(m_pShader->BeginPass(i)))
			{
				MSG_BOX(__FILE__, L"Shader BeginPass Failed");
				ABORT;
			}

			if (pGC->GetMesh()->GetMeshData()->GetMeshType() == (_int)EMeshType::Static)
			{
				const CStaticMesh* pSM = dynamic_cast<const CStaticMesh*>(pGC->GetMesh()->GetMeshData());
				
				for (_ulong i = 0; i < pSM->GetSubsetCount(); ++i)
				{
					if (FAILED(GET_DEVICE->SetTexture(0, pGC->GetTexture()->GetTexData()[i]->pTexture)))
					{
						int a = 5;
						int b = a;
					}

					m_pShader->SetTexture(m_pShader->GetParameterByName(0, "baseTex"), pGC->GetTexture()->GetTexData()[i]->pTexture);
					pSM->GetMesh()->DrawSubset(i);
				}
			}
			else if (pGC->GetMesh()->GetMeshData()->GetMeshType() == (_int)EMeshType::Dynamic)
			{

			}
			m_pShader->EndPass();

		}

		m_pShader->End();
	}
}

void CTextureShader::PostRender(CGraphicsC* pGraphics)
{
}

void CTextureShader::OnDestroy(void)
{
}

void CTextureShader::OnEnable(void)
{
}

void CTextureShader::OnDisable(void)
{
}

void CTextureShader::LoadShader(void)
{
	__super::LoadShader();
}
