#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include <d3d10.h>
#include <directxmath.h>
using namespace DirectX;

class ZModel
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ZModel();
	ZModel(const ZModel&);
	~ZModel();
	bool Initialize(ID3D10Device* device);
	void Shutdown();
	void Render(ID3D10Device* context);
	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D10Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D10Device* context);

private:
	ID3D10Buffer* m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif
