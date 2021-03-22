#ifndef WNDAPP_H
#define WNDAPP_H

/****************For Basic Windows****************/
#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_CLIENT_DIALOG		102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_CLIENT				107
#define IDI_SMALL				108
#define IDC_CLIENT				109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif
// 다음은 새 개체에 사용할 기본값입니다.
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif
/*************************************************/

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CWndApp final : public CEngine
{
DECLARE_SINGLETON	(CWndApp)

public:
					void				Awake				(void) override;
					void				Start				(HINSTANCE hInstance, int nCmdShow);

					void				OnDestroy			(void);

					void				OnEnable			(void);
					void				OnDisable			(void);

	
private:
					ATOM				RegisterWndClass	(HINSTANCE hInstance);
					bool				CreateWndHandle		(HINSTANCE hInstance, int nCmdShow);
	
	static			LRESULT	CALLBACK	WndProc				(HWND hWnd, UINT msg, 
															 WPARAM wParam, LPARAM lParam);	


	
	GETTOR			(_bool,				m_enable,			true,					Enable)

	GETTOR_SETTOR   (HWND,				m_hWnd,				NULL,					HWnd)

	GETTOR			(std::wstring,		m_className,		L"",					ClassName)
	GETTOR			(std::wstring,		m_windowName,		L"",					WindowName)

	GETTOR_SETTOR	(_int,				m_wndWidth,			0,						WndWidth)
	GETTOR_SETTOR	(_int,				m_wndHeight,		0,						WndHeight)

	GETTOR_SETTOR	(EDisplayMdoe,		m_displayMode,		EDisplayMdoe::WinMode,	DisplayMode)
};
END

#endif