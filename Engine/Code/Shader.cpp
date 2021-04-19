#include "EngineStdafx.h"
#include "Shader.h"
#include "DeviceManager.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"

USING(Engine)
CShader::CShader()
{
}


CShader::~CShader()
{
}

void CShader::Awake(void)
{
	__super::Awake();
}

void CShader::LoadShader(void)
{
	D3DXCreateEffectFromFile(GET_DEVICE, m_filePath.c_str(), 
							 nullptr, nullptr, 0, nullptr, &m_pShader, nullptr);

	if (m_pShader == nullptr)
	{
		MSG_BOX(__FILE__, L"Create Effect failed in LoadShader");
		ABORT;
	}
}

void CShader::RenderStaticMesh(CGraphicsC* pGC)
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

void CShader::RenderDynamicMesh(CGraphicsC* pGC)
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
