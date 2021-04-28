#include "EngineStdafx.h"
#include "DeviceManager.h"
#include "WndApp.h"

USING(Engine)
IMPLEMENT_SINGLETON(CDeviceManager)

void CDeviceManager::Awake(void)
{
	__super::Awake();
}

void CDeviceManager::Start(void)
{
	InitDevice();
}

void CDeviceManager::OnDestroy(void)
{
	m_pDevice->Release();
	m_pD3D->Release();
}

void CDeviceManager::OnEnable(void)
{
}

void CDeviceManager::OnDisable(void)
{
}

void CDeviceManager::InitDevice(void)
{
	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		MSG_BOX(__FILE__, L"Direct3D creation failed in InitDevice");
		ABORT;
	}

	DWORD vp = 0;
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	ZeroMemory(&m_d3dpParm, sizeof(m_d3dpParm));
	m_d3dpParm.BackBufferWidth				= CWndApp::GetInstance()->GetWndWidth();
	m_d3dpParm.BackBufferHeight				= CWndApp::GetInstance()->GetWndHeight();
	m_d3dpParm.BackBufferFormat				= D3DFMT_A8R8G8B8;
	m_d3dpParm.BackBufferCount				= 1;

	m_d3dpParm.MultiSampleType				= D3DMULTISAMPLE_NONE;
	m_d3dpParm.MultiSampleQuality			= 0;

	m_d3dpParm.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	m_d3dpParm.hDeviceWindow				= CWndApp::GetInstance()->GetHWnd();
	m_d3dpParm.Windowed						= (_int)CWndApp::GetInstance()->GetDisplayMode();
	m_d3dpParm.EnableAutoDepthStencil		= TRUE;
	m_d3dpParm.AutoDepthStencilFormat		= D3DFMT_D24S8;

	m_d3dpParm.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	m_d3dpParm.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;

	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
								   CWndApp::GetInstance()->GetHWnd(),
								   vp, 
								   &m_d3dpParm, &m_pDevice)))
	{
		MSG_BOX(__FILE__, L"Device creation failed in InitDevice");
		ABORT;
	}
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}
