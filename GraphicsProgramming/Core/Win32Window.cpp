#include "Win32Window.h"

using namespace Craft;

Win32Window::Win32Window(uint32_t _width, uint32_t _height, const wstring& _wstrTitle, HINSTANCE _inst, WNDPROC _msgProc)
	:m_iWidth(_width), m_iHeight(_height),m_wstrTitle(_wstrTitle), m_hInstance(_inst), m_MsgProc(_msgProc)
{

}

Win32Window::~Win32Window()
{
	//release window registration
	UnregisterClass(m_wstrClassName.c_str(), m_hInstance);
}

bool Win32Window::Init()
{
	//fill up struct needed for a new window
	WNDCLASS wc = {};
	wc.lpfnWndProc = m_MsgProc;
	wc.hInstance = m_hInstance;//program pointer
	wc.lpszClassName = m_wstrClassName.c_str();

	//register class
	if (!RegisterClass(&wc))
	{
		return 0;
	}

	//get window size.
	RECT rt = {};
	rt.left = 0, rt.top = 0;
	rt.right = m_iWidth, rt.bottom = m_iHeight;
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	//window size.
	uint32_t iWindowWidth = rt.right - rt.left;
	uint32_t iWindowHeight = rt.bottom - rt.top;

	//set the initial window position.
	//GetSystemMetrics(SM_CXSCREEN) returns your monitor resolution.
	//so it means 2560 - 1280
	uint32_t iWindowInitialPosX = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2;
	uint32_t iWindowInitialPosY = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

	//create window instance.
	m_hWnd = CreateWindow(
		m_wstrClassName.c_str(),//window class
		m_wstrTitle.c_str(),//window text
		WS_OVERLAPPEDWINDOW,//window style
		//pos and size
		iWindowInitialPosX, iWindowInitialPosY,
		iWindowWidth, iWindowHeight,
		nullptr,//hWndParent
		nullptr,//hMenu
		m_hInstance,//instance handle
		nullptr//additional app data
	);

	if (!m_hWnd)//failed to create window.
		return false;


	//get the size of client area(excluding the title bar from the window size)
	/*RECT rc = {};
	GetClientRect(hWnd, &rc);*/



	//set the window to be visible
	ShowWindow(m_hWnd, SW_SHOW);

	return true;
}

