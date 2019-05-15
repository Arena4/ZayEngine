#include "texture.h"
#include "DDSTextureLoader.h"

ZTexture::ZTexture()
{
	m_texture = 0;
}

ZTexture::ZTexture(const ZTexture& texture)
{
	
}

ZTexture::~ZTexture()
{
	
}

bool ZTexture::Initialize(ID3D11Device* device, WCHAR* name)
{
	HRESULT result;

	//result = D3DX10CreateShaderResourceViewFromFile(device, name, NULL, NULL, &m_texture, NULL);

	result = DirectX::CreateDDSTextureFromFile(device, name, NULL, &m_texture);

	if (FAILED(result))
		return false;

	return true;
}

void ZTexture::Shutdown()
{
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}

ID3D11ShaderResourceView* ZTexture::GetTexture()
{
	return m_texture;
}

