#include <windows.h>
#include <string>
#include <stdint.h>
#include "Core/Win32Window.h"
#include "Graphics/GraphicsContext.h"
using namespace Craft;
using namespace std;

//a callback function
//we use this when we process the window message
LRESULT CALLBACK WindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

int main() {
	//the name required for telling the OS about a new window (must be a unique name)
	wstring wstrClassName = L"Craft Engine Window";
	//use API and draw on the window.
	//Win32 API.
	wstring wstrTitle = L"Graphics Engine";


	// client size.
	uint32_t iClientWidth = 1280;
	uint32_t iClientHeight = 720;

	
	
	//fill up struct needed for a new window
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	Win32Window window(iClientWidth, iClientHeight, wstrTitle, hInstance, WindowProc);
	if (!window.Init())
		return -1;

	//test graphic device
	GraphicsContext context;
	context.Init(window);

	//run the message loop.
	MSG msg = {};
	//getmessage: sync method(blocking)
	//peekmessage: async method(non-blocking)
	//sync means there will be no other actions until current process is done.
	//async means it will go ahead even current process isn't over.
	//while (GetMessage(&msg, NULL, 0, 0) > 0)
	while(msg.message != WM_QUIT)//it will run until there is a WM_QUIT(quit program) message.
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE ))
		{
			//loop to proceess the messages that happen on the window.
			TranslateMessage(&msg);
			//send the translated message to dispatch function.
			DispatchMessage(&msg);
		}
		else {
			//engine logic.
		}
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT pt;
		HDC hdc = BeginPaint(hWnd, &pt);

		FillRect(hdc, &pt.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hWnd, &pt);
		return 0;
	}

	case WM_KEYDOWN: {
		switch (wParam) {
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
	}

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}