#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#include <d3d10.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>

using namespace DirectX;
using namespace std;

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
	bool Initialize(ID3D10Device* device, HWND hwnd);
	bool Render(ID3D10Device* context, int indexCount, XMMATRIX wolrdMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void Shutdown();

private:
	bool InitializeShader(ID3D10Device* device, HWND hwnd, WCHAR* vsFile, WCHAR* psFile);
	void ShutdownShader();
	void OutputSHaderErrorMessage(ID3D10Blob* message, HWND hwnd, WCHAR* shaderFile);
	bool SetShaderParameters(ID3D10Device* device, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void RenderShader(ID3D10Device* device, int indexCount);

private:
	ID3D10VertexShader* m_vertexShader;
	ID3D10PixelShader* m_pixelShader;
	ID3D10InputLayout* m_layout;
	ID3D10Buffer* m_matrixBuffer;
};

#endif
