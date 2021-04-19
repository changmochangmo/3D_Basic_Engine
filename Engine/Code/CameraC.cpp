#include "EngineStdafx.h"
#include "CameraC.h"
#include "Object.h"
#include "WndApp.h"
#include "Frustum.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "FRC.h"
#include "TextManager.h"

USING(Engine)
CCameraC::CCameraC()
{
}

CCameraC::~CCameraC()
{
	OnDestroy();
}



SP(CComponent) CCameraC::MakeClone(CObject * pObject)
{
	SP(CCameraC) spClone(new CCameraC, SmartDeleter<CCameraC>);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CCameraC::Awake(void)
{
	__super::Awake();
	m_pFrustum = CFrustum::Create(this);

	m_componentID = (_int)m_s_componentID;
}

void CCameraC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_spTransform = m_pOwner->GetComponent<CTransformC>();

}

void CCameraC::FixedUpdate(SP(CComponent) spThis)
{
}

void CCameraC::Update(SP(CComponent) spThis)
{
	if(GET_MAIN_CAM == spThis && m_mode != ECameraMode::Fixed)
		Move();

	if (m_updateView = m_spTransform->GetHasChanged())
		UpdateViewMatrix();

	if (m_updateProj)
		UpdateProjMatrix();

	if (m_updateProj || m_updateView)
	{
		m_pFrustum->Update();
		m_updateView = false;
		m_updateProj = false;
	}
}

void CCameraC::LateUpdate(SP(CComponent) spThis)
{
}

void CCameraC::OnDestroy(void)
{
	m_pFrustum->Free();
}

void CCameraC::OnEnable(void)
{
}

void CCameraC::OnDisable(void)
{
}

void CCameraC::SetNear(_float nearPlane)
{
	m_near = nearPlane;
	m_updateProj = true;
}

void CCameraC::SetFar(_float farPlane)
{
	m_far = farPlane;
	m_updateProj = true;
}

void CCameraC::SetFOV(_float FOV)
{
	m_FOV = FOV;
	m_updateProj = true;
}

void CCameraC::UpdateViewMatrix(void)
{	
	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMat, 
					   &m_spTransform->GetPosition(), 
					   &(m_spTransform->GetPosition() + m_spTransform->GetForward()),
					   &m_spTransform->GetUp());
}

void CCameraC::UpdateProjMatrix(void)
{
	D3DXMatrixPerspectiveFovLH(&m_projMat, m_FOV, 
							   (_float)GET_WND_WIDTH / GET_WND_HEIGHT, 
							   m_near, m_far);
}

void CCameraC::Move(void)
{
	Translation();
	Rotation();
}

void CCameraC::Translation(void)
{
	if (m_moveable)
	{
		if (IMKEY_PRESS(KEY_D))
			m_spTransform->MoveRight(30 * GET_DT);
		if (IMKEY_PRESS(KEY_A))
			m_spTransform->MoveLeft(30 * GET_DT);
		if (IMKEY_PRESS(KEY_W))
			m_spTransform->MoveForward(30 * GET_DT);
		if (IMKEY_PRESS(KEY_S))
			m_spTransform->MoveBackward(30 * GET_DT);
		if (IMKEY_PRESS(KEY_SPACE))
			m_spTransform->MoveUp(30 * GET_DT);
		if (IMKEY_PRESS(KEY_CONTROL))
			m_spTransform->MoveDown(30 * GET_DT);
	}
}

void CCameraC::Rotation(void)
{
	if (m_mode == ECameraMode::Edit)
	{
		if (IMKEY_PRESS(MOUSE_RIGHT))
		{
			if (m_rotatable == false)
				CInputManager::GetInstance()->ResetMousePosDelta();

			m_rotatable = true;
		}
		else
		{
			m_rotatable = false;
		}


		if (m_rotatable)
		{
			CInputManager* pIM = CInputManager::GetInstance();

			_float3 mousePosDelta = pIM->GetMousePosDelta();
			mousePosDelta.x = D3DXToRadian(mousePosDelta.x * pIM->GetMouseSensitivity().x) * GET_DT;
			mousePosDelta.y = D3DXToRadian(mousePosDelta.y * pIM->GetMouseSensitivity().y) * GET_DT;


			m_spTransform->AddRotation(_float3(mousePosDelta.y, -mousePosDelta.x, 0));
		}
	}
	else if (m_mode == ECameraMode::FPS)
	{
		CInputManager* pIM = CInputManager::GetInstance();
		if (m_rotatable == false)
		{
			m_rotatable = true;
			pIM->MoveMouseToCenter();
			pIM->ResetMousePosDelta();
		}

		if (m_rotatable)
		{
			POINT curPt;
			GetCursorPos(&curPt);
			POINT m_centerPt = { Engine::GET_WND_WIDTH >> 1, Engine::GET_WND_HEIGHT >> 1 };
			ClientToScreen(Engine::GET_HANDLE, &m_centerPt);
			SetCursorPos(m_centerPt.x, m_centerPt.y);
			

			m_spTransform->AddRotationX(D3DXToRadian((_float)(curPt.y - m_centerPt.y) 
													 * pIM->GetMouseSensitivity().y 
													 * GET_DT));
			m_spTransform->AddRotationY(D3DXToRadian((_float)(curPt.x - m_centerPt.x) 
													 * pIM->GetMouseSensitivity().x 
													 * GET_DT));
		}
	}

}
