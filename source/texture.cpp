#include "texture.h"

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

bool ZTexture::Initialize(ID3D10Device* device, WCHAR* name)
{
	HRESULT result;

	//result = D3DX10CreateShaderResourceViewFromFile(device, name, NULL, NULL, &m_texture, NULL);

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

