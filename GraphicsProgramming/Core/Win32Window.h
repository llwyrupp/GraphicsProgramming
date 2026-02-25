#pragma once
#ifndef __WIN32WINDOW_H__
#define __WIN32WINDOW_H__

#include <windows.h>
#include <string>
#include <stdint.h>
using namespace std;

namespace Craft{
	//a window class using win32 api
	class Win32Window
	{
	public:
		Win32Window(uint32_t _width = 1280, uint32_t _height = 720, HINSTANCE _inst = nullptr, WNDPROC _msgProc = nullptr);
		~Win32Window();
	public:
		//init funcs
		bool Init();
	public:
		//getter
		inline uint32_t GetWidth() const { return m_iWidth; }
		inline uint32_t GetHeight() const { return m_iHeight; }
		inline HWND GetHandle() const { return m_hWnd; }

	private:
		//titles
		wstring m_wstrTitle = L"Graphics Programming";
		//the class name used for window registration.
		wstring m_wstrClassName = L"Craft Engine";

		//size of the window.
		uint32_t m_iWidth = 0;
		uint32_t m_iHeight = 0;

		//window instance(the handle)
		HWND m_hWnd = nullptr;
		//program pointer(instance)
		HINSTANCE m_hInstance = nullptr;
		//function pointer to process messages.
		WNDPROC m_MsgProc = nullptr;
	};
}

#endif//!__WIN32WINDOW_H__