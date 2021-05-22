#ifndef LOADING_H
#define LOADING_H

#include "Scene.h"

class CLoading
{
public:
	explicit						CLoading				(void);
								   ~CLoading				(void);

public:
	static		_uint	__stdcall	ThreadMain				(void* pArg);		
public:
	static		CLoading*			Create					(_int loadingID);
				void				Free					(void);
				void				StartLoading			(_int loadingID);
				_uint				LoadBossScene			(void);


private:
	GETTOR		(HANDLE,			m_threadHandle,			{},				ThreadHandle)
	GETTOR		(CRITICAL_SECTION,	m_crt,					{},				CriticalSection)
	GETTOR		(_int,				m_loadingID,			UNDEFINED,		LoadingID)
	GETTOR		(_bool,				m_finish,				false,			Finish)
	GETTOR		(std::wstring,		m_msg,					L"",			Message)

	GETTOR_SETTOR	(Engine::CScene*,	m_pNextScene,		nullptr,		NextScene)
};

#endif