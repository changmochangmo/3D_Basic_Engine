#include "EngineStdafx.h"
#include "Frustum.h"
#include "CameraC.h"

USING(Engine)
CFrustum::CFrustum()
{
}


CFrustum::~CFrustum()
{
}

CFrustum * CFrustum::Create(CCameraC* pOwner)
{
	CFrustum* pFrustum = new CFrustum;
	pFrustum->SetOwner(pOwner);
	
	return pFrustum;
}

void CFrustum::Free(void)
{
	delete this;
}

void CFrustum::Awake(void)
{
}

void CFrustum::Update(void)
{
	D3DXMATRIX frustumMatrix = m_pOwner->GetViewMatrix() * m_pOwner->GetProjMatrix();

	// Calculate near plane of frustum.
	m_plane[0].a = frustumMatrix._14 + frustumMatrix._13;
	m_plane[0].b = frustumMatrix._24 + frustumMatrix._23;
	m_plane[0].c = frustumMatrix._34 + frustumMatrix._33;
	m_plane[0].d = frustumMatrix._44 + frustumMatrix._43;
	D3DXPlaneNormalize(&m_plane[0], &m_plane[0]);

	// Calculate far plane of frustum.
	m_plane[1].a = frustumMatrix._14 - frustumMatrix._13;
	m_plane[1].b = frustumMatrix._24 - frustumMatrix._23;
	m_plane[1].c = frustumMatrix._34 - frustumMatrix._33;
	m_plane[1].d = frustumMatrix._44 - frustumMatrix._43;
	D3DXPlaneNormalize(&m_plane[1], &m_plane[1]);

	// Calculate left plane of frustum.
	m_plane[2].a = frustumMatrix._14 + frustumMatrix._11;
	m_plane[2].b = frustumMatrix._24 + frustumMatrix._21;
	m_plane[2].c = frustumMatrix._34 + frustumMatrix._31;
	m_plane[2].d = frustumMatrix._44 + frustumMatrix._41;
	D3DXPlaneNormalize(&m_plane[2], &m_plane[2]);

	// Calculate right plane of frustum.
	m_plane[3].a = frustumMatrix._14 - frustumMatrix._11;
	m_plane[3].b = frustumMatrix._24 - frustumMatrix._21;
	m_plane[3].c = frustumMatrix._34 - frustumMatrix._31;
	m_plane[3].d = frustumMatrix._44 - frustumMatrix._41;
	D3DXPlaneNormalize(&m_plane[3], &m_plane[3]);

	// Calculate top plane of frustum.
	m_plane[4].a = frustumMatrix._14 - frustumMatrix._12;
	m_plane[4].b = frustumMatrix._24 - frustumMatrix._22;
	m_plane[4].c = frustumMatrix._34 - frustumMatrix._32;
	m_plane[4].d = frustumMatrix._44 - frustumMatrix._42;
	D3DXPlaneNormalize(&m_plane[4], &m_plane[4]);

	// Calculate bottom plane of frustum.
	m_plane[5].a = frustumMatrix._14 + frustumMatrix._12;
	m_plane[5].b = frustumMatrix._24 + frustumMatrix._22;
	m_plane[5].c = frustumMatrix._34 + frustumMatrix._32;
	m_plane[5].d = frustumMatrix._44 + frustumMatrix._42;
	D3DXPlaneNormalize(&m_plane[5], &m_plane[5]);
}

void CFrustum::LateUpdate(void)
{
}

void CFrustum::OnEnable(void)
{
}

void CFrustum::OnDisable(void)
{
}

_bool CFrustum::CheckPoint(_float3 position)
{
	for (_uint i = 0; i < 6; ++i)
	{
		if (D3DXPlaneDotCoord(&m_plane[i], &position) < 0.f)
			return false;
	}

	return true;
}

_bool CFrustum::CheckAabb(_float3 position, _float3 halfExtent)
{
	for (_uint i = 0; i < 2; ++i)
	{
		for (_uint j = 0; j < 2; ++j)
		{
			for (_uint k = 0; k < 2; ++k)
			{
				_int xSign = i ? 1 : -1;
				_int ySign = j ? 1 : -1;
				_int zSign = k ? 1 : -1;

				_float3 curExtent = _float3(halfExtent.x * xSign,
											 halfExtent.y * ySign,
											 halfExtent.z * zSign);

				if (CheckPoint(position + curExtent))
					return true;
			}
		}
	}

	return false;
}

_bool CFrustum::CheckSphere(_float3 position, _float radius)
{
	for (_uint i = 0; i < 6; ++i)
	{
		if (D3DXPlaneDotCoord(&m_plane[i], &position) < -radius)
			return false;
	}

	return true;
}

void CFrustum::OnDestroy(void)
{
}
