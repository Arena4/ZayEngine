#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>

#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;

class ZShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ZShader();
	~ZShader();
	bool Initialize(ID3D11Device* device, HWND hwnd);
	bool Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX wolrdMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void Shutdown();

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFile, WCHAR* psFile);
	void ShutdownShader();
	void OutputSHaderErrorMessage(ID3D10Blob* message, HWND hwnd, WCHAR* shaderFile);
	bool SetShaderParameters(ID3D11DeviceContext* device, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void RenderShader(ID3D11DeviceContext* device, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};

#endif
