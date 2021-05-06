#ifndef GRID_H
#define GRID_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CGrid final : public CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CGrid				(void);
								   ~CGrid				(void);

public:
	static		SP(CGrid)			Create				(_bool isStatic);

				SP(CObject)			MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

private:
				void				SetBasicName		(void) override;
private:
	static		_uint				m_s_uniqueID;

	GETTOR		(SP(CMeshC),		m_spMesh,			nullptr,	Mesh)
	GETTOR		(SP(CGraphicsC),	m_spGraphics,		nullptr,	Graphics)
};
END
#endif