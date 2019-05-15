#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include <d3d11.h>
#include <directxmath.h>
#include "texture.h"

using namespace DirectX;

class ZModel
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT3 texture;
	};

public:
	ZModel();
	ZModel(const ZModel&);
	~ZModel();
	bool Initialize(ID3D11Device* device, WCHAR* name);
	void Shutdown();
	void Render(ID3D11DeviceContext* context);
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* context);
	bool LoadTexture(ID3D11Device* device, WCHAR* name);
	void ReleaseTexture();

private:
	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	ZTexture* m_Texture;
};

#endif
