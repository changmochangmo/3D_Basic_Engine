#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CInputManager final : public CEngine
{
	DECLARE_SINGLETON(CInputManager)
public:
					void					Awake				(void) override;
					void					Start				(void);

					_uint					FixedUpdate			(void);
					_uint					Update				(void);
					_uint					LateUpdate			(void);	

					void					OnDestroy			(void);

					void					OnEnable			(void);
					void					OnDisable			(void);

					bool					KeyUp				(DWORD key);
					bool					KeyDown				(DWORD key);
					bool					KeyPress			(DWORD key);
					CGameObject*			MousePicking		(std::wstring layerKey, _float3& intersection);
					CGameObject*			RayCast				(_float3 origin, _float3 direction, _float maxDistance, std::wstring layerKey);
private:
					void					KeyUpdate			(void);
					void					MouseUpdate			(void);


					_float3					GetPickingDirection	(void);
					_bool					RayIntersectCheck	(_float rayAxisDir, _float rayAxisStart,
																 _float aabbAxisMin, _float aabbAxisMax,
																 _float& tMin, _float& tMax);
private:
					DWORD					m_key;
					DWORD					m_lastFrameKey;

	GETTOR			(_float3,				m_mousePos,		_float3(0, 0, 0),	MousePos)
};
END

#endif