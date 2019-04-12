#pragma once

#ifndef _D3D_H_
#define _D3D_H_

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3D11.lib")

#include <dxgi.h>
#include <D3Dcommon.h>
#include <D3D11.h>
#include <D3D9types.h>

class D3D
{
public:
	D3D();
	~D3D();
	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();
	void BeginScene(float, float, float, float);
	void EndScene();
	void GetProjectionMatrix(D3DMATRIX&);
	void GetWorldMatrix(D3DMATRIX&);
	void GetOrthoMatrix(D3DMATRIX&);
	void GetVideoCardInfo(char*, int&);
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	D3DMATRIX *D3DMatrixIdentity(D3DMATRIX *pOut);
	D3DMATRIX* D3DMatrixPerspectiveFovLH(D3DMATRIX *pout, FLOAT fovy, FLOAT aspect, FLOAT zn, FLOAT zf);
	D3DMATRIX* D3DMatrixOrthoLH(D3DMATRIX *pout, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf);

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	D3DMATRIX m_projectionMatrix;
	D3DMATRIX m_worldMatrix;
	D3DMATRIX m_orthoMatrix;
};

#endif

