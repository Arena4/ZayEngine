#include "shader.h"

ZShader::ZShader()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
}

ZShader::~ZShader()
{

}

bool ZShader::Initialize(ID3D11Device * device, HWND hwnd)
{
	bool result = InitializeShader(device, hwnd, L"data/Texture.vs.hlsl", L"data/Texture.ps.hlsl");

	return result;
}

bool ZShader::Render(ID3D11DeviceContext * context, int indexCount, XMMATRIX wolrdMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	bool result = SetShaderParameters(context, wolrdMatrix, viewMatrix, projectionMatrix, texture);
	if (!result) return false;

	RenderShader(context, indexCount);

	return true;
}

void ZShader::Shutdown()
{
	ShutdownShader();
}

bool ZShader::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR * vsFile, WCHAR * psFile)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//Compile the vertex shader code.
	result = D3DCompileFromFile(vsFile, NULL, NULL, "TextureVertexShader", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertexShaderBuffer, &errorMessage);
	if(FAILED(result))
	{
		if (errorMessage)
			OutputSHaderErrorMessage(errorMessage, hwnd, vsFile);
		else
			MessageBox(hwnd, vsFile, L"Missing Shader File", MB_OK);

		return false;
	}

	//Compile the pixel shader code.
	result = D3DCompileFromFile(psFile, NULL, NULL, "TexturePixelShader", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixelShaderBuffer, &errorMessage);
	if(FAILED(result))
	{
		if (errorMessage)
			OutputSHaderErrorMessage(errorMessage, hwnd, psFile);
		else
			MessageBox(hwnd, psFile, L"Missing Shader File", MB_OK);
	}

	//Create Shader from buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
		return false;

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
		return false;

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
		return false;

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;
	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	//Setup the description of dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
		return false;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ZShader::ShutdownShader()
{
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	if(m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
}

void ZShader::OutputSHaderErrorMessage(ID3D10Blob * message, HWND hwnd, WCHAR * shaderFile)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;

	compileErrors = (char*)(message->GetBufferPointer());
	bufferSize = message->GetBufferSize();
	fout.open("shader-error.txt");

	for(i = 0;i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	message->Release();
	message = 0;

	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFile, MB_OK);
}

bool ZShader::SetShaderParameters(ID3D11DeviceContext* device, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = device->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
		return false;

	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;
	device->Unmap(m_matrixBuffer, 0);
	bufferNumber = 0;
	device->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	device->PSSetShaderResources(0, 1, &texture);

	return true;
}

void ZShader::RenderShader(ID3D11DeviceContext* context, int indexCount)
{
	context->IASetInputLayout(m_layout);
	context->VSSetShader(m_vertexShader, NULL, 0);
	context->PSSetShader(m_pixelShader, NULL, 0);
	context->DrawIndexed(indexCount, 0, 0);
	context->PSSetSamplers(0, 1, &m_sampleState);
	context->DrawIndexed(indexCount, 0, 0);
}
