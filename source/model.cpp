#include "model.h"

ZModel::ZModel()
{
	m_indexCount = 0;
	m_vertexCount = 0;
}

ZModel::ZModel(const ZModel &)
{
}

ZModel::~ZModel()
{
}

bool ZModel::Initialize(ID3D11Device * device)
{
	bool result = InitializeBuffers(device);

	return result;
}

void ZModel::Shutdown()
{
	ShutdownBuffers();
}

void ZModel::Render(ID3D11DeviceContext * context)
{
	RenderBuffers(context);
}

int ZModel::GetIndexCount()
{
	return m_indexCount;
}

bool ZModel::InitializeBuffers(ID3D11Device * device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 3;
	m_indexCount = 3;
	
	vertices = new VertexType[m_vertexCount];
	indices = new unsigned long[m_indexCount];

	//init vertex & index data.
	vertices[0].position =  { -1.f, -1.f, 0.f, 0.0f};
	vertices[0].color = { 0.0f, 1.0f, 0.0f, 1.0f };

	vertices[1].position = { 0.0f, 1.0f, 0.0f, 0.0f };
	vertices[1].color = { 0.0f, 1.0f, 0.0f, 1.0f };

	vertices[2].position = { 1.0f, -1.0f, 0.0f, 0.0f };
	vertices[2].color = { 0.0f, 1.0f, 0.0f, 1.0f };

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	//Setup the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create vertext buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
		return false;

	//Setup the description of the static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ZModel::ShutdownBuffers()
{
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

void ZModel::RenderBuffers(ID3D11DeviceContext * context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}