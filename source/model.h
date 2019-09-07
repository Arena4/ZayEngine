#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
#include "texture.h"

using namespace DirectX;
using namespace std;

class ZModel
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT3 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ZModel();
	
	ZModel(const ZModel&);
	
	~ZModel();
	
	bool Initialize(ID3D11Device* device, char*, WCHAR* name);
	
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
	
	bool LoadModel(char*);
	
	void ReleaseModel();

private:
	int m_vertexCount, m_indexCount;

	ID3D11Buffer* m_vertexBuffer, *m_indexBuffer;
	
	ZTexture* m_Texture;
	
	ModelType* m_model;
};

#endif
