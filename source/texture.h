#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d11.h>

class ZTexture
{
public:
	ZTexture();
	ZTexture(const ZTexture&);
	~ZTexture();

	bool Initialize(ID3D11Device* device, WCHAR* name);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};

#endif