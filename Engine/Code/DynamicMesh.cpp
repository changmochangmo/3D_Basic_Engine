#include "EngineStdafx.h"
#include "DynamicMesh.h"
#include "StaticMesh.h"
#include "DeviceManager.h"

USING(Engine)
CDynamicMesh::CDynamicMesh()
{
}


CDynamicMesh::~CDynamicMesh()
{
}

CMesh * CDynamicMesh::MakeClone(void)
{
	CDynamicMesh* pClone = new CDynamicMesh;

	pClone->m_pRootFrame = m_pRootFrame;
	pClone->m_pHierarchyLoader = m_pHierarchyLoader;
	pClone->m_pAniCtrl = m_pAniCtrl->MakeClone();
	pClone->m_vMeshContainers = m_vMeshContainers;
	pClone->m_meshType = m_meshType;
	pClone->m_vMeshContainers = m_vMeshContainers;

	return pClone;
}

void CDynamicMesh::FreeClone(void)
{
	OnDestory();
}

void CDynamicMesh::Awake(std::wstring const& filePath, std::wstring const& fileName)
{
	m_meshType = (_int)EMeshType::Dynamic;

	m_pHierarchyLoader = CHierarchyLoader::Create(filePath, this);

	LPD3DXANIMATIONCONTROLLER pAniCtrl = nullptr;

	if (FAILED(D3DXLoadMeshHierarchyFromX((filePath + L"\\" + fileName).c_str(),
		D3DXMESH_MANAGED,
		GET_DEVICE,
		m_pHierarchyLoader,
		NULL,
		&m_pRootFrame,
		&pAniCtrl)))
	{
		MSG_BOX(__FILE__, L"Load Mesh Hierarchy failed in ParsingMesh");
		ABORT;
	}


	m_pAniCtrl = CAniCtrl::Create(pAniCtrl);
	m_pAniCtrl->ChangeAniSet(FindFirstAniIndex(fileName));
	UpdateFrame();
	SetFrameMatPointer((_DerivedD3DXFRAME*)m_pRootFrame);
}

void CDynamicMesh::Start(void)
{

}

void CDynamicMesh::Update(void)
{
	m_pAniCtrl->Play();
}

void CDynamicMesh::OnDestory(void)
{
	m_pAniCtrl->Free();
	delete this;
}

CDynamicMesh * CDynamicMesh::Create(std::wstring const & filePath, std::wstring const & fileName)
{
	CDynamicMesh* pDynamicMesh = new CDynamicMesh;
	pDynamicMesh->Awake(filePath, fileName);

	return pDynamicMesh;
}

void CDynamicMesh::Free(void)
{
	m_pHierarchyLoader->DestroyFrame(m_pRootFrame);
	m_pHierarchyLoader->Free();
	OnDestory();
}

void CDynamicMesh::UpdateFrame(void)
{
	_mat makeMeshLookAtMe;
	UpdateFrameMatrices((_DerivedD3DXFRAME*)m_pRootFrame,
		D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f)));

}

void CDynamicMesh::ChangeAniSet(_uint index)
{
	m_pAniCtrl->ChangeAniSet(index);
}

void CDynamicMesh::ChangeAniSet(std::string name)
{
	m_pAniCtrl->ChangeAniSet(name);
}

void CDynamicMesh::PlayAnimation(void)
{
	m_pAniCtrl->Play();

	UpdateFrame();
}

_DerivedD3DXFRAME * CDynamicMesh::GetFrameByName(std::string name)
{
	return (_DerivedD3DXFRAME*)D3DXFrameFind(m_pRootFrame, name.c_str());
}

_bool CDynamicMesh::IsAnimationEnd(void)
{
	return m_pAniCtrl->IsItEnd();
}

void CDynamicMesh::UpdateFrameMatrices(_DerivedD3DXFRAME* pFrame, _mat* pParentMat)
{
	if (pFrame == nullptr)
		return;

	pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix * (*pParentMat);

	if (pFrame->pFrameSibling != nullptr)
		UpdateFrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameSibling, pParentMat);

	if (pFrame->pFrameFirstChild != nullptr)
		UpdateFrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild, &pFrame->CombinedTransformMatrix);

}

void CDynamicMesh::SetFrameMatPointer(_DerivedD3DXFRAME * pFrame)
{

	if (pFrame->pMeshContainer != nullptr)
	{
		_DerivedD3DXMESHCONTAINER*	pDerivedMeshContainer = (_DerivedD3DXMESHCONTAINER*)pFrame->pMeshContainer;

		for (_ulong i = 0; i < pDerivedMeshContainer->numBones; ++i)
		{
			std::string			pBoneName = pDerivedMeshContainer->pSkinInfo->GetBoneName(i);
			_DerivedD3DXFRAME* pFindFrame = (_DerivedD3DXFRAME*)D3DXFrameFind(m_pRootFrame, pBoneName.c_str());
			pDerivedMeshContainer->ppCombinedTransformMatrix[i] = &pFindFrame->CombinedTransformMatrix;

			pDerivedMeshContainer->pOriMesh;
		}

		m_vMeshContainers.push_back(pDerivedMeshContainer);
	}

	if (nullptr != pFrame->pFrameSibling)
		SetFrameMatPointer((D3DXFRAME_DERIVED*)pFrame->pFrameSibling);

	if (nullptr != pFrame->pFrameFirstChild)
		SetFrameMatPointer((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild);
}

_uint CDynamicMesh::FindFirstAniIndex(std::wstring const & fileName)
{
	_size startPoint = fileName.find_first_of('.');
	_size endPoint = fileName.find_last_of('.');

	if (startPoint == endPoint)
		return 0;
	else
		return std::stoi(fileName.substr(++startPoint, endPoint - startPoint));
}
