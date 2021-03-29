#include "EngineStdafx.h"
#include "Camera.h"
#include "GameObject.h"
#include "WndApp.h"
#include "Frustum.h"
#include "CameraManager.h"

USING(Engine)
CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

CCamera * CCamera::Create(void)
{
	CCamera* pCamera = new CCamera;
	pCamera->Awake();

	return pCamera;
}

void CCamera::Free(void)
{
	OnDestroy();
	delete this;
}

void CCamera::Awake(void)
{
	__super::Awake();
	m_pFrustum = CFrustum::Create(this);
}

void CCamera::Start(void)
{
}

void CCamera::Update(void)
{
	if (m_pOwner)
	{
		SHARED(CTransformComponent) spOwnerTransform = m_pOwner->GetComponent<CTransformComponent>();
		m_position = spOwnerTransform->GetPosition();
		m_rotation = spOwnerTransform->GetRotation();
	}

	UpdateViewMatrix();
	UpdateProjMatrix();

	m_pFrustum->Update();
}

void CCamera::LateUpdate(void)
{
}

void CCamera::OnDestroy(void)
{
	m_pFrustum->Free();
}

void CCamera::OnEnable(void)
{
}

void CCamera::OnDisable(void)
{
}

void CCamera::UpdateViewMatrix(void)
{
	_float3 up, eye, lookAt;
	_float yaw, pitch, roll;
	_mat rotationMatrix;

	up		= UP_VECTOR;
	lookAt = FORWARD_VECTOR;
	eye		= m_position;

	yaw		= D3DXToRadian(m_rotation.y);
	pitch	= D3DXToRadian(m_rotation.x);
	roll	= D3DXToRadian(m_rotation.z);

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = lookAt;
	m_up = up;

	lookAt = eye + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMat, &eye, &lookAt, &up);
}

void CCamera::UpdateProjMatrix(void)
{
	D3DXMatrixPerspectiveFovLH(&m_projMat, m_FOV, 
							   (_float)GET_WND_WIDTH / GET_WND_HEIGHT, 
							   m_near, m_far);
}

