#include "EngineStdafx.h"
#include "CameraComponent.h"
#include "WndApp.h"
#include "DeviceManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "DataStore.h"

USING(Engine)
CCameraComponent::CCameraComponent(void)
{
}

CCameraComponent::~CCameraComponent(void)
{
}

SHARED(CComponent) CCameraComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CCameraComponent) pClone(new CCameraComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetViewMatrix(m_matView);
	pClone->SetProjMatrix(m_matProj);

	pClone->SetAt(m_at);
	pClone->SetUp(m_up);

	pClone->SetTempAt(m_tAt);
	pClone->SetTempUp(m_tUp);

	pClone->SetMouseSensitivity(m_mouseSensitivity);
	pClone->SetMoveSpeed(m_moveSpeed);

	pClone->m_centerPt = m_centerPt;

	return pClone;
}

void CCameraComponent::Awake(void)
{
	__super::Awake();
	
	m_componentID = (int)m_s_componentID;

	RECT rect;

	GetClientRect(Engine::CWndApp::GetInstance()->GetHWnd(), &rect);

	// 화면 밖으로 못 나가게 한다.
	POINT p1, p2;
	p1.x = rect.left;
	p1.y = rect.top;
	p2.x = rect.right;
	p2.y = rect.bottom;

	ClientToScreen(Engine::CWndApp::GetInstance()->GetHWnd(), &p1);
	ClientToScreen(Engine::CWndApp::GetInstance()->GetHWnd(), &p2);

	rect.left = p1.x;
	rect.top = p1.y;
	rect.right = p2.x;
	rect.bottom = p2.y;

	m_centerPt.x = (p1.x + p2.x) / 2;
	m_centerPt.y = (p1.y + p2.y) / 2;
	SetCursorPos(m_centerPt.x, m_centerPt.y);
	m_previousFramePt = m_centerPt;

	m_at.x = 0.f;
	m_at.y = 0.f;
	m_at.z = 1.f;
	m_tAt = m_at;

	m_up.x = 0.f;
	m_up.y = 1.f;
	m_up.z = 0.f;
	m_tUp = m_up;

	m_sectionKey = m_pOwner->GetLayerKey();
	m_objectKey = GetCurClassName(this);
}

// 에디터에서는 마우스를 고정하지않는다 처음에는
// 우클릭했을때만 고정한다.

void CCameraComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	GET_VALUE(true, m_sectionKey, m_objectKey, L"m_moveSpeed", m_moveSpeed);
	GET_VALUE(true, m_sectionKey, m_objectKey, L"m_mouseSensitivity", m_mouseSensitivity);
	GET_VALUE(true, m_sectionKey, m_objectKey, L"m_near", m_near);
	GET_VALUE(true, m_sectionKey, m_objectKey, L"m_far", m_far);
	GET_VALUE(true, m_sectionKey, m_objectKey, L"m_fov", m_fov);
	m_pTransform = m_pOwner->GetComponent<CTransformComponent>();
	m_isCameraEvent = false;
}

_uint CCameraComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

unsigned int CCameraComponent::Update(SHARED(CComponent) spThis)
{
	MaitrxCalculate();
	FrustumUpdate();

	// 카메라의 이동값
	POINT curPt;
	GetCursorPos(&curPt);
	m_mouseDelta.x = static_cast<_float>(m_previousFramePt.x - curPt.x);
	m_mouseDelta.y = static_cast<_float>(m_previousFramePt.y - curPt.y);
	m_previousFramePt = curPt;

	return _uint();
}

unsigned int CCameraComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}


void CCameraComponent::OnDestroy(void)
{
}

void CCameraComponent::OnEnable(void)
{
}

void CCameraComponent::OnDisable(void)
{
}

void CCameraComponent::CameraMove()
{
	_float speed = 300.f;
	if (Engine::IMKEY_PRESS(KEY_SHIFT))
	{
		speed = 4;
	}

	if (Engine::IMKEY_PRESS(KEY_W))
	{
		m_pTransform->Translate(FLOAT3_FORWARD * GET_DT * speed);
	}

	if (Engine::IMKEY_PRESS(KEY_S))
	{
		m_pTransform->Translate(FLOAT3_BACK * GET_DT * speed);
	}

	if (Engine::IMKEY_PRESS(KEY_A))
	{

		m_pTransform->Translate(FLOAT3_LEFT * GET_DT * speed);
	}
	if (Engine::IMKEY_PRESS(KEY_D))
	{
		m_pTransform->Translate(FLOAT3_RIGHT * GET_DT * speed);
	}
}

void CCameraComponent::CameraRotation()
{
	POINT curPt;
	GetCursorPos(&curPt);
	SetCursorPos(m_centerPt.x, m_centerPt.y);

	// 카메라 회전
	if (curPt.y < m_centerPt.y) // mouse up look
	{
		_float angleY = GET_DT * (abs(curPt.y - m_centerPt.y) * m_mouseSensitivity);
		m_pTransform->AddRotationX(-1 * angleY);
	}

	if (curPt.y > m_centerPt.y) // mouse down look
	{
		_float angleY = GET_DT * (abs(curPt.y - m_centerPt.y) * m_mouseSensitivity);
		m_pTransform->AddRotationX(angleY);
	}

	if (curPt.x < m_centerPt.x) // mouse left look
	{
		_float angleX = CFRC::GetInstance()->GetDeltaTime() * (abs(curPt.x - m_centerPt.x) * m_mouseSensitivity);
		m_pTransform->AddRotationY(-1 * angleX);
	}

	if (curPt.x > m_centerPt.x) // mouse right look
	{
		_float angleX = CFRC::GetInstance()->GetDeltaTime() * (abs(curPt.x - m_centerPt.x) * m_mouseSensitivity);
		m_pTransform->AddRotationY(angleX);
	}	

}

void CCameraComponent::MaitrxCalculate()
{
	m_tAt = m_at;
	m_tUp = m_up;

	_mat rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, D3DXToRadian(m_pTransform->GetRotation().y), D3DXToRadian(m_pTransform->GetRotation().x), D3DXToRadian(m_pTransform->GetRotation().z));
	D3DXVec3TransformCoord(&m_tAt, &m_tAt, &rotationMatrix);
	D3DXVec3TransformCoord(&m_tUp, &m_tUp, &rotationMatrix);

	m_tAt += m_pTransform->GetPosition();

	D3DXMatrixLookAtLH(&m_matView, &m_pTransform->GetPosition(), &m_tAt, &m_tUp);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(m_fov), 800 / 600.f, m_near, m_far);
	D3DXMatrixOrthoLH(&m_matOrtho, 800, 600, 0, m_far);
}

void CCameraComponent::FrustumUpdate()
{
	D3DXMATRIX M = m_matView * m_matProj;

	m_leftPlane.a = M._14 + M._11;
	m_leftPlane.b = M._24 + M._21;
	m_leftPlane.c = M._34 + M._31;
	m_leftPlane.d = M._44 + M._41;
	D3DXPlaneNormalize(&m_leftPlane, &m_leftPlane);

	m_rightPlane.a = M._14 - M._11;
	m_rightPlane.b = M._24 - M._21;
	m_rightPlane.c = M._34 - M._31;
	m_rightPlane.d = M._44 - M._41;
	D3DXPlaneNormalize(&m_rightPlane, &m_rightPlane);

	m_topPlane.a = M._14 + M._12;
	m_topPlane.b = M._24 + M._22;
	m_topPlane.c = M._34 + M._32;
	m_topPlane.d = M._44 + M._42;
	D3DXPlaneNormalize(&m_topPlane, &m_topPlane);

	m_bottomPlane.a = M._14 + M._12;
	m_bottomPlane.b = M._24 + M._22;
	m_bottomPlane.c = M._34 + M._32;
	m_bottomPlane.d = M._44 + M._42;
	D3DXPlaneNormalize(&m_bottomPlane, &m_bottomPlane);

	m_nearPlane.a = M._13;
	m_nearPlane.b = M._23;
	m_nearPlane.c = M._33;
	m_nearPlane.d = M._43;
	D3DXPlaneNormalize(&m_nearPlane, &m_nearPlane);

	m_farPlane.a = M._14 - M._13;
	m_farPlane.b = M._24 - M._23;
	m_farPlane.c = M._34 - M._33;
	m_farPlane.d = M._44 - M._43;
	D3DXPlaneNormalize(&m_farPlane, &m_farPlane);
}

_bool CCameraComponent::IsInFrustum(_float3 & position)
{
	/*
	면과 위치를 내적했을 때 0보다 크면 안에 있는 것
	작으면 밖, 0이면 동일한 위치
	여섯 면을 모두 검사한다.
	*/
	if (D3DXPlaneDotCoord(&m_leftPlane, &position) < -1.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_rightPlane, &position) < -1.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_topPlane, &position) < -1.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_bottomPlane, &position) < -1.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_nearPlane, &position) < -1.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_farPlane, &position) < -1.0f)
		return false;

	return true;
}