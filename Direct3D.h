#ifndef DIRECT3D_H
#define DIRECT3D_H

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

class Direct3D
{
public:
	Direct3D();
	~Direct3D();

	bool Initialize(HWND hWnd, int width, int height);
	void Begin();
	void End();
	void Uninitialize();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Context;
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
};

#endif // DIRECT3D_H
