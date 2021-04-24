#include "EngineStdafx.h"
#include "TextureShader.h"
#include "DeviceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"


USING(Engine)
CTextureShader::CTextureShader()
{
}

CTextureShader::~CTextureShader()
{
}

CTextureShader * CTextureShader::Create(void)
{
	CTextureShader* pInstance = new CTextureShader;
	pInstance->Awake();
	pInstance->Start();

	return pInstance;
}

void CTextureShader::Awake(void)
{
	__super::Awake();
	m_filePath = L"..\\..\\Resource\\Shader\\TextureShader.fx";
	m_shaderType = (_int)EShaderType::Texture;
}

void CTextureShader::Start(void)
{
	LoadShader();
}

void CTextureShader::PreRender(CGraphicsC* pGC)
{
	__super::PreRender(pGC);
	m_pShader->SetVector("Color", &pGC->GetTexture()->GetColor());
}

void CTextureShader::Render(CGraphicsC * pGC)
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
			_int meshType = pGC->GetMesh()->GetMeshData()->GetMeshType();

			switch (meshType)
			{
			case (_int)EMeshType::Static:
				RenderStaticMesh(pGC);
				break;

			case (_int)EMeshType::Dynamic:
				RenderDynamicMesh(pGC);
				break;

			default:
				break;
			}

			m_pShader->EndPass();
		}

		m_pShader->End();
	}
}


void CTextureShader::PostRender(CGraphicsC* pGC)
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

void CTextureShader::RenderStaticMesh(CGraphicsC * pGC)
{
	CStaticMesh* pSM = dynamic_cast<CStaticMesh*>(pGC->GetMesh()->GetMeshData());

	for (_ulong i = 0; i < pSM->GetSubsetCount(); ++i)
	{
		if (FAILED(GET_DEVICE->SetTexture(0, pGC->GetTexture()->GetTexData()[i]->pTexture)))
		{
			MSG_BOX(__FILE__, L"SetTexture failed in RenderStaticMesh");
			ABORT;
		}
		pSM->GetMesh()->DrawSubset(i);
	}
}

void CTextureShader::RenderDynamicMesh(CGraphicsC * pGC)
{
	CDynamicMesh* pDM = dynamic_cast<CDynamicMesh*>(pGC->GetMesh()->GetMeshData());

	pDM->GetAniCtrl()->GetAniCtrl()->AdvanceTime(0, NULL);
	pDM->UpdateFrame();

	for (auto& meshContainer : pDM->GetMeshContainers())
	{
		for (_ulong i = 0; i < meshContainer->numBones; ++i)
		{
			meshContainer->pRenderingMatrix[i] = meshContainer->pFrameOffsetMatrix[i] *
												 (*meshContainer->ppCombinedTransformMatrix[i]);
		}

		void* pSrcVertex = nullptr;
		void* pDestVertex = nullptr;

		meshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVertex);
		meshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVertex);

		meshContainer->pSkinInfo->UpdateSkinnedMesh(meshContainer->pRenderingMatrix, NULL,
													pSrcVertex, pDestVertex);

		meshContainer->MeshData.pMesh->UnlockVertexBuffer();
		meshContainer->pOriMesh->UnlockVertexBuffer();

		for (_ulong i = 0; i < meshContainer->NumMaterials; ++i)
		{
			GET_DEVICE->SetTexture(0, pGC->GetTexture()->GetTexData()[meshContainer->texIndexStart + i]->pTexture);
			meshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
