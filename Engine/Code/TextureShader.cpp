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

			const std::vector<CMeshData*>& vMeshData = pGC->GetMesh()->GetMeshDatas();
			for (_int i = 0; i < (_int)vMeshData.size(); ++i)
			{

				_int meshType = vMeshData[i]->GetMeshType();

				switch (meshType)
				{
				case (_int)EMeshType::Static:
					RenderStaticMesh(pGC, i);
					break;

				case (_int)EMeshType::Dynamic:
					RenderDynamicMesh(pGC, i);
					break;

				default:
					break;
				}
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

void CTextureShader::RenderStaticMesh(CGraphicsC * pGC, _int index)
{
	CStaticMesh* pSM = dynamic_cast<CStaticMesh*>(pGC->GetMesh()->GetMeshDatas()[index]);

	for (_ulong i = 0; i < pSM->GetSubsetCount(); ++i)
	{
		_TexData* pTexData = pGC->GetTexture()->GetTexData()[index][i];

		if (pTexData != nullptr)
			GET_DEVICE->SetTexture(0, pGC->GetTexture()->GetTexData()[index][i]->pTexture);
		else
			GET_DEVICE->SetTexture(0, nullptr);
		
		pSM->GetMesh()->DrawSubset(i);
	}
}

void CTextureShader::RenderDynamicMesh(CGraphicsC * pGC, _int index)
{
	CDynamicMesh* pDM = dynamic_cast<CDynamicMesh*>(pGC->GetMesh()->GetMeshDatas()[index]);

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

		const std::vector<std::vector<_TexData*>>& pTexData = pGC->GetTexture()->GetTexData();
		for (_ulong i = 0; i < meshContainer->NumMaterials; ++i)
		{
			if (pTexData[index][i] != nullptr)
				GET_DEVICE->SetTexture(0, pTexData[index][i]->pTexture);
			else
				GET_DEVICE->SetTexture(0, nullptr);

			meshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
