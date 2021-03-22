#ifndef RESOURCESTORE_H
#define RESOURCESTORE_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CResourceStore abstract : public CEngine
{
public:
	explicit							CResourceStore			(void);
	virtual							   ~CResourceStore			(void);

public:
	virtual			void				Awake					(void) PURE;
	virtual			void				Start					(void) PURE;
	virtual			void				OnDestroy				(void) PURE;
					
	virtual			void				ClearCurResource		(void) PURE;
protected:
	virtual			void				InitResource			(std::wstring sourcePath) PURE;
	

	std::function<void(std::wstring, std::wstring)>	m_fpResourceHandler;

	GETTOR			(std::wstring,		m_resourcePath,			L"",		ResourcePath)
	GETTOR			(_bool,				m_isStatic,				true,		IsStatic);
};

END
#endif