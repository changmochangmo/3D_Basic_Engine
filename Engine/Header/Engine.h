#ifndef ENGINE_H
#define ENGINE_H

BEGIN(Engine)
class ENGINE_DLL CEngine abstract
{
public:
	explicit		CEngine		(void);
	virtual		   ~CEngine		(void);

public:
	virtual		void	Awake		(void) PURE;

protected:
	GETTOR		(_int,			m_sectionKey,	(_int)EDataID::Engine,	SectionKey)
	GETTOR		(std::wstring,	m_objectKey,	L"",					ObjectKey)
};
END
#endif