#include "EngineStdafx.h"
#include "InputManager.h"
#include "WndApp.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Layer.h"
#include "CameraManager.h"
#include "CameraC.h"
#include "TextManager.h"
#include "DataStore.h"

USING(Engine)
IMPLEMENT_SINGLETON(CInputManager)

void CInputManager::Awake(void)
{
	__super::Awake();
}


void CInputManager::Start(void)
{
	GET_VALUE(true, m_dataID, m_objectKey, L"mouseSensitivity", m_mouseSensitivity);
}

void CInputManager::FixedUpdate(void)
{
}

void CInputManager::Update(void)
{
	KeyUpdate();
	MouseUpdate();
}

void CInputManager::LateUpdate(void)
{
}

void CInputManager::OnDestroy(void)
{
}

void CInputManager::OnEnable(void)
{
}

void CInputManager::OnDisable(void)
{
}
bool CInputManager::KeyUp(DWORD key)
{
	if ((m_lastFrameKey & key) && !(m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyDown(DWORD key)
{
	if (!(m_lastFrameKey & key) && (m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyPress(DWORD key)
{
	if (m_key & key)
		return true;

	return false;
}

void CInputManager::KeyUpdate(void)
{
	m_lastFrameKey = m_key;
	m_key = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_key |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_key |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_key |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_key |= KEY_DOWN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_key |= KEY_SPACE;
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_key |= KEY_CONTROL;
	if (GetAsyncKeyState(VK_F1) & 0x8000)
		m_key |= KEY_F1;
	if (GetAsyncKeyState(VK_F2) & 0x8000)
		m_key |= KEY_F2;
	if (GetAsyncKeyState(VK_F3) & 0x8000)
		m_key |= KEY_F3;
	if (GetAsyncKeyState(VK_F4) & 0x8000)
		m_key |= KEY_F4;
	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_key |= KEY_F5;
	if (GetAsyncKeyState(0x57) & 0x8000)
		m_key |= KEY_W;
	if (GetAsyncKeyState(0x41) & 0x8000)
		m_key |= KEY_A;
	if (GetAsyncKeyState(0x53) & 0x8000)
		m_key |= KEY_S;
	if (GetAsyncKeyState(0x44) & 0x8000)
		m_key |= KEY_D;
	if (GetAsyncKeyState('E') & 0x8000)
		m_key |= KEY_E;
	if (GetAsyncKeyState('Q') & 0x8000)
		m_key |= KEY_Q;
	if (GetAsyncKeyState('1') & 0x8000)
		m_key |= KEY_1;
	if (GetAsyncKeyState('2') & 0x8000)
		m_key |= KEY_2;
	if (GetAsyncKeyState('3') & 0x8000)
		m_key |= KEY_3;
	if (GetAsyncKeyState('4') & 0x8000)
		m_key |= KEY_4;
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		m_key |= KEY_TAB;
	if (GetAsyncKeyState(VK_DELETE) & 0x8000)
		m_key |= KEY_DELETE;
	if (GetAsyncKeyState('Z') & 0x8000)
		m_key |= KEY_Z;
	if (GetAsyncKeyState('X') & 0x8000)
		m_key |= KEY_X;
}

void CInputManager::MouseUpdate(void)
{
	m_mouseLastFramePos = m_mousePos;

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(GET_HANDLE, &p);

	m_mousePos = _float3((_float)p.x, (_float)p.y, 0);

	m_mousePos.x -= (GET_WND_WIDTH / 2.f);
	m_mousePos.y = (m_mousePos.y * -1) + GET_WND_HEIGHT / 2.f;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_key |= MOUSE_LEFT;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_key |= MOUSE_RIGHT;
}

void CInputManager::MoveMouseToCenter(void)
{
	m_mouseLastFramePos = m_mousePos;
	POINT mousePos = { GET_WND_WIDTH >> 1, GET_WND_HEIGHT >> 1 };;
	ClientToScreen(GET_HANDLE, &mousePos);
	SetCursorPos(mousePos.x, mousePos.y);

	m_mousePos = _float3(0, 0, 0);
}

CGameObject * CInputManager::MousePicking(_int layerID, _float3& intersection)
{
	_float3 rayStartPos = GET_MAIN_CAM->GetTransform()->GetPosition(); // 원점
	_float3 rayDir = GetPickingDirection(); // 방향

	_float t = FLT_MAX;
	CGameObject* pGameObject = nullptr;

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerID];

	for (auto& object : pLayer->GetGameObjects())
	{
		_float tMin = GET_MAIN_CAM->GetNear();
		_float tMax = GET_MAIN_CAM->GetFar(); // 거리

 		auto& pTransform = object->GetComponent<CTransformC>();

		_float3 minPos = _float3(-0.5f, -0.5f, -0.5f);
		_float3 maxPos = _float3(0.5f, 0.5f, 0.5f);

		D3DXVec3TransformCoord(&minPos, &minPos, &pTransform->GetWorldMatrix());
		D3DXVec3TransformCoord(&maxPos, &maxPos, &pTransform->GetWorldMatrix());


		if (!RayIntersectCheck(rayDir.x, rayStartPos.x, 
							   minPos.x, maxPos.x,
							   tMin, tMax))
			continue;
		if (!RayIntersectCheck(rayDir.y, rayStartPos.y, 
							   minPos.y, maxPos.y,
							   tMin, tMax))
			continue;
		if (!RayIntersectCheck(rayDir.z, rayStartPos.z, 
							   minPos.z, maxPos.z,
							   tMin, tMax))
			continue;

		if (tMin < t)
		{
			t = tMin;
			pGameObject = object.get();
		}
	}
	
	intersection = rayStartPos + t * rayDir;
	return pGameObject;
}

_float3 CInputManager::GetMousePosDelta(void)
{
	return (m_mousePos - m_mouseLastFramePos);
}

void CInputManager::ResetMousePosDelta(void)
{
	m_mouseLastFramePos = m_mousePos;
}


_float3 CInputManager::GetPickingDirection(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(GET_HANDLE, &pt);

	/* 뷰포트 -> 투영스페이스 */
	_float3 vMouse;
	vMouse.x = pt.x / (GET_WND_WIDTH * 0.5f) - 1.f;
	vMouse.y = 1.f - pt.y / (GET_WND_HEIGHT * 0.5f);
	vMouse.z = 0.f;

	_mat matInvProj;
	D3DXMatrixInverse(&matInvProj, 0, &GET_MAIN_CAM->GetProjMatrix());
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matInvProj);

	_float3 rayDir = vMouse;
	D3DXVec3Normalize(&rayDir, &rayDir);

	_mat matInvView;
	D3DXMatrixInverse(&matInvView, 0, &GET_MAIN_CAM->GetViewMatrix());
	D3DXVec3TransformNormal(&rayDir, &rayDir, &matInvView);
	D3DXVec3Normalize(&rayDir, &rayDir);


	return rayDir;
}

_bool CInputManager::RayIntersectCheck(_float rayAxisDir, _float rayAxisStart, 
									   _float aabbAxisMin, _float aabbAxisMax, 
									   _float& tMin, _float& tMax)
{
	if (abs(rayAxisDir) < EPSILON)
	{
		//no hit if origin not within axis
		if (rayAxisStart < aabbAxisMin || rayAxisStart > aabbAxisMax)
			return false;
	}
	else
	{
		//compute intersection t value of near and far plane of axis
		float ood = 1.f / rayAxisDir;
		float t1 = (aabbAxisMin - rayAxisStart) * ood;
		float t2 = (aabbAxisMax - rayAxisStart) * ood;
		//make t1 be intersection with near plane, t2 with far
		if (t1 > t2)
		{
			_float temp = t1;
			t1 = t2;
			t2 = temp;
		}

		//compute intersection on axis 
		if (t1 > tMin)
			tMin = t1;
		if (t2 < tMax)
			tMax = t2;

		//Exit with no collision as soon as intersection becomes empty
		if (tMin > tMax)
			return false;
	}

	return true;
}

