#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CObject;
class ENGINE_DLL CInputManager final : public CEngine
{
	DECLARE_SINGLETON(CInputManager)
public:
					void					Awake					(void) override;
					void					Start					(void);

					void					FixedUpdate				(void);
					void					Update					(void);
					void					LateUpdate				(void);	

					void					OnDestroy				(void);

					void					OnEnable				(void);
					void					OnDisable				(void);

					_bool					KeyUp					(DWORD key);
					_bool					KeyDown					(DWORD key);
					_bool					KeyPress				(DWORD key);

					void					MoveMouseToCenter		(void);
					CObject*				MousePicking			(_int layerID, _float3& intersection);

					_float3					GetMousePosDelta		(void);
					void					ResetMousePosDelta		(void);
private:
					void					KeyUpdate				(void);
					void					MouseUpdate				(void);


					_float3					GetPickingDirection		(void);
					_bool					RayIntersectCheck		(_float rayAxisDir, _float rayAxisStart,
																	 _float aabbAxisMin, _float aabbAxisMax,
																	 _float& tMin, _float& tMax);
private:
					DWORD					m_key			= 0;
					DWORD					m_lastFrameKey	= 0;

	
	GETTOR			(_float3,				m_mousePos,				ZERO_VECTOR,		MousePos)
	GETTOR			(_float3,				m_mouseLastFramePos,	ZERO_VECTOR,		MouseLastFramePos)
	GETTOR			(_float2,				m_mouseSensitivity,		_float2(PI, PI),	MouseSensitivity)
	GETTOR_SETTOR	(_float,				m_mouseWheelDir,		0.f,				MouseWheelDir)
};
END

#endif