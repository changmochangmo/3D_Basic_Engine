#include "EngineStdafx.h"
#include "HierarchyLoader.h"
#include "DeviceManager.h"
#include "TextureStore.h"
#include "DynamicMesh.h"

USING(Engine)
CHierarchyLoader::CHierarchyLoader(const std::wstring path)
	: m_path(path)
{
}


CHierarchyLoader::~CHierarchyLoader()
{
}

STDMETHODIMP CHierarchyLoader::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	_DerivedD3DXFRAME* pDerivedFrame = new _DerivedD3DXFRAME;
	ZeroMemory(pDerivedFrame, sizeof(_DerivedD3DXFRAME));

	//Name�� pDerivedFrame->Name�� �Ҵ�.
	AllocateName(&pDerivedFrame->Name, Name);

	D3DXMatrixIdentity(&pDerivedFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pDerivedFrame->CombinedTransformMatrix);

	*ppNewFrame = pDerivedFrame;
	return S_OK;
}

STDMETHODIMP CHierarchyLoader::CreateMeshContainer(THIS_ LPCSTR Name, 
												   CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, 
												   CONST D3DXEFFECTINSTANCE* pEffectInstances, 
												   DWORD NumMaterials, CONST DWORD* pAdjacency, 
												   LPD3DXSKININFO pSkinInfo, 
												   LPD3DXMESHCONTAINER* ppNewMeshContainer)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//�����̳� ����� ����!
	_DerivedD3DXMESHCONTAINER* pDerivedMeshContainer = new _DerivedD3DXMESHCONTAINER;
	ZeroMemory(pDerivedMeshContainer, sizeof(_DerivedD3DXMESHCONTAINER));

	//���� �����̳��� ���µ��� �� �ؽ��ĸ� ã�� ���� �ؽ��� �ε��� ���۰��� ����ݴϴ�.
	//m_curTexLastIndex�� ���� ������ index�� + 1 �����Դϴ�
	pDerivedMeshContainer->texIndexStart = m_curTexLastIndex;
	m_curTexLastIndex += NumMaterials;

	//�̸��� �־��ݴϴ�.
	AllocateName(&pDerivedMeshContainer->Name, Name);

	//�޽� �������� Ÿ�� ����
	pDerivedMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH pMesh = pMeshData->pMesh;

	//�� ���̽��� ������ ���̽��� 3���� �����Ƿ�, pAdjacency�� ���̽� ���� * 3���� �޸𸮸� �Ҵ�
	pDerivedMeshContainer->pAdjacency = new _ulong[pMesh->GetNumFaces() * 3];
	memcpy(pDerivedMeshContainer->pAdjacency, pAdjacency, sizeof(_ulong) * pMesh->GetNumFaces() * 3);

	//�޾ƿ� FVF�� pDerivedMeshContainer�� FVF ����.
	_ulong	dwFVF = pMesh->GetFVF();

	// �޽��� �븻 ������ ���� ��� �ڵ�� ����
	if (!(dwFVF & D3DFVF_NORMAL))
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF | D3DFVF_NORMAL, pDevice, 
							&pDerivedMeshContainer->MeshData.pMesh);

		// ������ ����� ������ �������� �븻 ���� ����� ��
		D3DXComputeNormals(pDerivedMeshContainer->MeshData.pMesh, pDerivedMeshContainer->pAdjacency);
	}
	else
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF, pDevice, &pDerivedMeshContainer->MeshData.pMesh);
	}

	//NumMaterials ����
	pDerivedMeshContainer->NumMaterials = (NumMaterials == 0 ? 1 : NumMaterials);

	//������ŭ �Ҵ�
	pDerivedMeshContainer->pMaterials = new D3DXMATERIAL[pDerivedMeshContainer->NumMaterials];
	ZeroMemory(pDerivedMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pDerivedMeshContainer->NumMaterials);

	//���� Materials�� �츮 Mtrl����
	if (0 != NumMaterials)
	{
		memcpy(pDerivedMeshContainer->pMaterials, pMaterials, 
			   sizeof(D3DXMATERIAL) * pDerivedMeshContainer->NumMaterials);

		for (_size i = 0; i < pDerivedMeshContainer->NumMaterials; ++i)
		{
			if(pDerivedMeshContainer->pMaterials[i].pTextureFilename != nullptr)
				m_pOwner->AddTexNameToList(StrToWStr(pDerivedMeshContainer->pMaterials[i].pTextureFilename));
		}
	}
	else
	{
		pDerivedMeshContainer->pMaterials[0].MatD3D.Diffuse = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedMeshContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedMeshContainer->pMaterials[0].MatD3D.Ambient = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedMeshContainer->pMaterials[0].MatD3D.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pDerivedMeshContainer->pMaterials[0].MatD3D.Power = 0.f;
	}

	//��Ų���� ������ �׳� ���ư� (�ִϸ��̼��� �ִ� ��� ����)
	if (nullptr == pSkinInfo)
		return S_OK;

	//��Ų������ �ް� ���۷��� ī��Ʈ++
	pDerivedMeshContainer->pSkinInfo = pSkinInfo;
	pDerivedMeshContainer->pSkinInfo->AddRef();

	//�Ʊ� �޾Ƽ� �־���� FVF�� �츮 pOriMesh�� FVF����
	pDerivedMeshContainer->MeshData.pMesh->CloneMeshFVF(pDerivedMeshContainer->MeshData.pMesh->GetOptions(), 
														dwFVF, pDevice, &pDerivedMeshContainer->pOriMesh);

	// �޽� �����̳ʿ� ������ ��ġ�� ���� ������ ��ȯ
	pDerivedMeshContainer->numBones = pDerivedMeshContainer->pSkinInfo->GetNumBones();

	//���� ������ŭ FrameOffsetMatrix, CombinedTransformMatrix, RenderingMatrix�� �ʿ��ϹǷ� �Ҵ�.
	pDerivedMeshContainer->pFrameOffsetMatrix = new _mat[pDerivedMeshContainer->numBones];
	ZeroMemory(pDerivedMeshContainer->pFrameOffsetMatrix, sizeof(_mat) * pDerivedMeshContainer->numBones);

	pDerivedMeshContainer->ppCombinedTransformMatrix = new _mat*[pDerivedMeshContainer->numBones];
	ZeroMemory(pDerivedMeshContainer->ppCombinedTransformMatrix, sizeof(_mat*) * pDerivedMeshContainer->numBones);

	pDerivedMeshContainer->pRenderingMatrix = new _mat[pDerivedMeshContainer->numBones];
	ZeroMemory(pDerivedMeshContainer->pRenderingMatrix, sizeof(_mat) * pDerivedMeshContainer->numBones);

	//�� �������� OffsetMatrix�� skinInfo�� �����ִ� BoneOffsetMatrix�� �־���.
	for (_ulong i = 0; i < pDerivedMeshContainer->numBones; ++i)
		pDerivedMeshContainer->pFrameOffsetMatrix[i] = *pDerivedMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);

	//���� �޽������̳� ��ȯ.
	*ppNewMeshContainer = pDerivedMeshContainer;

	return S_OK;
}

STDMETHODIMP CHierarchyLoader::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	SafeDeleteArray(pFrameToFree->Name);

	if (nullptr != pFrameToFree->pMeshContainer)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);

	if (nullptr != pFrameToFree->pFrameSibling)
		DestroyFrame(pFrameToFree->pFrameSibling);

	if (nullptr != pFrameToFree->pFrameFirstChild)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	SafeDelete(pFrameToFree);

	return S_OK;
}

STDMETHODIMP CHierarchyLoader::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	_DerivedD3DXMESHCONTAINER*	pDerivedMeshContainer = (_DerivedD3DXMESHCONTAINER*)pMeshContainerToFree;

	SafeDeleteArray(pDerivedMeshContainer->pMaterials);
	SafeDeleteArray(pDerivedMeshContainer->pAdjacency);

	pDerivedMeshContainer->MeshData.pMesh->Release();
	pDerivedMeshContainer->pOriMesh->Release();
	pDerivedMeshContainer->pSkinInfo->Release();

	SafeDeleteArray(pDerivedMeshContainer->Name);
	SafeDeleteArray(pDerivedMeshContainer->pFrameOffsetMatrix);
	SafeDeleteArray(pDerivedMeshContainer->ppCombinedTransformMatrix);
	SafeDeleteArray(pDerivedMeshContainer->pRenderingMatrix);

	SafeDelete(pDerivedMeshContainer);

	return S_OK;
}

CHierarchyLoader * CHierarchyLoader::Create(const std::wstring path, CDynamicMesh* pOwner)
{
	CHierarchyLoader* pHL = new CHierarchyLoader(path);
	pHL->m_pOwner = pOwner;
	return pHL;
}

void CHierarchyLoader::Free(void)
{
	delete this;
}

void CHierarchyLoader::AllocateName(char ** ppName, const char * pFrameName)
{
	if (nullptr == pFrameName)
		return;

	_size length = strlen(pFrameName);

	*ppName = new char[length + 1];

	strcpy_s(*ppName, length + 1, pFrameName);
}
