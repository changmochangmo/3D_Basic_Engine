#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CGraphicsManager final : public CEngine
{
	DECLARE_SINGLETON(CGraphicsManager)

public:
			void					Awake				(void) override;
			void					Start				(void);

			_uint					FixedUpdate			(void);
			_uint					Update				(void);
			_uint					LateUpdate			(void);	

			_uint					PreRender			(void);
			_uint					Render				(void);
			_uint					PostRender			(void);

			void					OnDestroy			(void);

			void					OnEnable			(void);
			void					OnDisable			(void);

			void					AddToRenderList		(_int renderID, 
														 SP(CGraphicsC) pGC);


private:
	typedef std::vector<SP(CGraphicsC)> _GRAPHICSCOMPONENTS;
			_GRAPHICSCOMPONENTS		m_vRenderList[(_uint)ERenderID::NumOfRenderID];
};
END
#endif