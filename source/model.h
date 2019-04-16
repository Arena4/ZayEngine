#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include <d3d11.h>
#include <d3d9types.h>
#include <DirectXMath.h>

using namespace DirectX;

class ZModel
{
private:
	struct VertexType
	{
		XMVECTOR position;
		XMVECTOR color;
	};

public:
	ZModel();
	ZModel(const ZModel&);
	~ZModel();
	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* context);
	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* context);

private:
	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif
