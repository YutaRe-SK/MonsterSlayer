#include "Direct3D.h"

Direct3D::Direct3D()
{
	m_Device = nullptr;
	m_Context = nullptr;
	m_SwapChain = nullptr;
	m_RenderTargetView = nullptr;
}

Direct3D::~Direct3D()
{
	Uninitialize();
}

bool Direct3D::Initialize(HWND hWnd, int width, int height)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;

	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_SwapChain,
		&m_Device,
		&featureLevel,
		&m_Context
	);

	if (FAILED(hr))return false;
	
	ID3D11Texture2D* backBuffer = nullptr;

	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	if (FAILED(hr))return false;

	hr = m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);

	backBuffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void Direct3D::Begin()
{
	float clearColor[4] = { 0.15f, 0.25f, 0.35f, 1.0f };

	m_Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);

	m_Context->ClearRenderTargetView(m_RenderTargetView, clearColor);
}

void Direct3D::End()
{
	m_SwapChain->Present(1, 0);
}

void Direct3D::Uninitialize()
{
	if (m_RenderTargetView)
	{
		m_RenderTargetView->Release();
		m_RenderTargetView = nullptr;
	}
	if (m_SwapChain)
	{
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}
	if (m_Context)
	{
		m_Context->Release();
		m_Context = nullptr;
	}
	if (m_Device)
	{
		m_Device->Release();
		m_Device = nullptr;
	}
}

ID3D11Device* Direct3D::GetDevice()
{
	return m_Device;
}

ID3D11DeviceContext* Direct3D::GetContext()
{
	return m_Context;
}