#include "../Graphics/GraphicsContext.h"
#include "../Core/Win32Window.h"
#include "../Common.h"

namespace Craft {
	GraphicsContext::GraphicsContext()
	{

	}
	GraphicsContext::~GraphicsContext()
	{
		/*if (m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = nullptr;
		}

		if (m_pDeviceContext)
		{
			m_pDeviceContext->Release();
			m_pDeviceContext = nullptr;
		}

		if (m_pSwapChain)
		{
			m_pSwapChain->Release();
			m_pSwapChain = nullptr;
		}*/
		SafeRelease(m_pDevice);
		SafeRelease(m_pDeviceContext);
		SafeRelease(m_pSwapChain);
	}
	void GraphicsContext::Init(const Win32Window& _window)
	{
		m_iHeight = _window.GetHeight();
		m_iWidth = _window.GetWidth();

		// 장치 생성.
		CreateDevice();

		// SwapChain 생성.
		CreateSwapChain(_window);

		// 뷰포트 생성.
		CreateViewport(_window);
	}
	void GraphicsContext::CreateDevice()
	{
		
		uint32_t flag = 0;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featLevel[] = { D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0 };


		if (FAILED(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featLevel,
			_countof(featLevel),
			D3D11_SDK_VERSION,
			&m_pDevice,
			nullptr,
			&m_pDeviceContext
		)))
		{
			__debugbreak();
			return;
		}
	}
	void GraphicsContext::CreateSwapChain(const Win32Window& _window)
	{
		//create swapchain.
		IDXGIFactory* pFactory = nullptr;
		IDXGIAdapter* pAdapter = nullptr;
		if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory))))
		{
			__debugbreak();
			return;
		}
		//settings for creating swapchain
		DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
		ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		SwapChainDesc.Windowed = TRUE;//start as window mode
		SwapChainDesc.OutputWindow = _window.GetHandle();
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.BufferCount = 2;
		//buffer swap effects.
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		//anti-aliasing, supersampling standard.
		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.SampleDesc.Count = 1;

		//settings for buffer(frame image)
		SwapChainDesc.BufferDesc.Width = _window.GetWidth();
		SwapChainDesc.BufferDesc.Height = _window.GetHeight();
		//an image pixel format(32bit, unsigned, normalized) 
		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;


		if (FAILED(pFactory->CreateSwapChain(m_pDevice, &SwapChainDesc, &m_pSwapChain)))
		{
			__debugbreak();
			return;
		}

		SafeRelease(pFactory);
	}
	void GraphicsContext::CreateViewport(const Win32Window& _window)
	{
		//뷰포트: 나눠서 사용가능
		//
		m_pViewPort.TopLeftX = 0.f;
		m_pViewPort.TopLeftY = 0.f;
		m_pViewPort.Width = static_cast<float>(_window.GetWidth());
		m_pViewPort.Height = static_cast<float>(_window.GetHeight());
		m_pViewPort.MinDepth = 0.f;
		m_pViewPort.MaxDepth = 1.f;
	}
}