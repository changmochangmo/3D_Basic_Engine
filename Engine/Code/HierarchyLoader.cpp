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

	//Name을 pDerivedFrame->Name에 할당.
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

	//컨테이너 만들기 시작!
	_DerivedD3DXMESHCONTAINER* pDerivedMeshContainer = new _DerivedD3DXMESHCONTAINER;
	ZeroMemory(pDerivedMeshContainer, sizeof(_DerivedD3DXMESHCONTAINER));

	//현재 컨테이너의 섭셋들이 쓸 텍스쳐를 찾기 위해 텍스쳐 인덱스 시작값을 잡아줍니다.
	//m_curTexLastIndex는 현재 마지막 index값 + 1 상태입니다
	pDerivedMeshContainer->texIndexStart = m_curTexLastIndex;
	m_curTexLastIndex += NumMaterials;

	//이름을 넣어줍니다.
	AllocateName(&pDerivedMeshContainer->Name, Name);

	//메쉬 데이터의 타입 세팅
	pDerivedMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH pMesh = pMeshData->pMesh;

	//각 페이스당 인접한 페이스가 3개씩 있으므로, pAdjacency에 페이스 숫자 * 3개의 메모리를 할당
	pDerivedMeshContainer->pAdjacency = new _ulong[pMesh->GetNumFaces() * 3];
	memcpy(pDerivedMeshContainer->pAdjacency, pAdjacency, sizeof(_ulong) * pMesh->GetNumFaces() * 3);

	//받아온 FVF로 pDerivedMeshContainer의 FVF 세팅.
	_ulong	dwFVF = pMesh->GetFVF();

	// 메쉬의 노말 정보가 없는 경우 코드로 삽입
	if (!(dwFVF & D3DFVF_NORMAL))
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF | D3DFVF_NORMAL, pDevice, 
							&pDerivedMeshContainer->MeshData.pMesh);

		// 인접한 면들의 정보를 기준으로 노말 값을 만들어 줌
		D3DXComputeNormals(pDerivedMeshContainer->MeshData.pMesh, pDerivedMeshContainer->pAdjacency);
	}
	else
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF, pDevice, &pDerivedMeshContainer->MeshData.pMesh);
	}

	//NumMaterials 세팅
	pDerivedMeshContainer->NumMaterials = (NumMaterials == 0 ? 1 : NumMaterials);

	//개수만큼 할당
	pDerivedMeshContainer->pMaterials = new D3DXMATERIAL[pDerivedMeshContainer->NumMaterials];
	ZeroMemory(pDerivedMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pDerivedMeshContainer->NumMaterials);

	//받은 Materials로 우리 Mtrl세팅
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

	//스킨정보 없으면 그냥 돌아감 (애니메이션이 있는 경우 있음)
	if (nullptr == pSkinInfo)
		return S_OK;

	//스킨인포를 받고 레퍼런스 카운트++
	pDerivedMeshContainer->pSkinInfo = pSkinInfo;
	pDerivedMeshContainer->pSkinInfo->AddRef();

	//아까 받아서 넣어놓은 FVF로 우리 pOriMesh의 FVF세팅
	pDerivedMeshContainer->MeshData.pMesh->CloneMeshFVF(pDerivedMeshContainer->MeshData.pMesh->GetOptions(), 
														dwFVF, pDevice, &pDerivedMeshContainer->pOriMesh);

	// 메쉬 컨테이너에 영향을 미치는 뼈의 개수를 반환
	pDerivedMeshContainer->numBones = pDerivedMeshContainer->pSkinInfo->GetNumBones();

	//뼈의 갯수만큼 FrameOffsetMatrix, CombinedTransformMatrix, RenderingMatrix가 필요하므로 할당.
	pDerivedMeshContainer->pFrameOffsetMatrix = new _mat[pDerivedMeshContainer->numBones];
	ZeroMemory(pDerivedMeshContainer->pFrameOffsetMatrix, sizeof(_mat) * pDerivedMeshContainer->numBones);

	pDerivedMeshContainer->ppCombinedTransformMatrix = new _mat*[pDerivedMeshContainer->numBones];
	ZeroMemory(pDerivedMeshContainer->ppCombinedTransformMatrix, sizeof(_mat*) * pDerivedMeshContainer->numBones);

	pDerivedMeshContainer->pRenderingMatrix = new _mat[pDerivedMeshContainer->numBones];
	ZeroMemory(pDerivedMeshContainer->pRenderingMatrix, sizeof(_mat) * pDerivedMeshContainer->numBones);

	//각 프레임의 OffsetMatrix에 skinInfo가 갖고있는 BoneOffsetMatrix를 넣어줌.
	for (_ulong i = 0; i < pDerivedMeshContainer->numBones; ++i)
		pDerivedMeshContainer->pFrameOffsetMatrix[i] = *pDerivedMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);

	//만든 메쉬컨테이너 반환.
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
