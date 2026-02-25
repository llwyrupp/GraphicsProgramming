#pragma once
#ifndef __GRAPHICSCONTEXT_H__
#define __GRAPHICSCONTEXT_H__

#include<d3d11.h>//direct3d 11 related header.
#include<dxgi.h>//dxgi dedvice related header.(swap chain)
#include<string>


// 장치(그래픽카드).
// Direct3D에서 "장치"로 다루는 객체는 3개.
// Device: 리소스 생성.
// DeviceContext: 생성된 리소스를 그래픽카드에 할당(바인딩)/드로우콜.
// SwapChain(스왑체인): 백버퍼-프론트버퍼 교환.
// 
//devicecontext: binding the resources to the graphic device.(Drawcall)
//SwapChain: the swap between the front and back buffers


using namespace std;
namespace Craft {
	//forward declaration
	class Win32Window;

	//graphics related attributes and manage graphics resources.
	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();
	public:
		void Init(uint32_t _width, uint32_t _height, const Win32Window& _window);
	private:
		// 장치류.
		// Direct3D 리소스는 포인터로만 다룰 수 있음.
		// 생성/해제를 API에 요청.
		//DEVICE:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext = nullptr;
		IDXGISwapChain* m_pSwapChain = nullptr;

		//VIEWPORT:
		D3D11_VIEWPORT m_pViewPort = {};

		//screen size
		uint32_t m_iWidth = 0;
		uint32_t m_iHeight = 0;
	};
}


#endif // !__GRAPHICSCONTEXT_H__