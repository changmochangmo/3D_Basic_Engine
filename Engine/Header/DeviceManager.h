#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CDeviceManager final : public CEngine
{
	DECLARE_SINGLETON(CDeviceManager)
public:
			void	Awake		(void) override;
			void	Start		(void);
		
			void	OnDestroy	(void);
		
			void	OnEnable	(void);
			void	OnDisable	(void);

private:
			void	InitDevice	(void);


private:
			D3DPRESENT_PARAMETERS	m_d3dpParm			= {};
			LPDIRECT3D9				m_pD3D				= nullptr;

	GETTOR	(LPDIRECT3DDEVICE9,		m_pDevice,			nullptr,			Device)
};
END
#endif