#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <DirectXMath.h>

using namespace DirectX;

class Light
{
public:
	Light();
	~Light();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	XMVECTOR GetDiffuseColor();
	XMVECTOR GetDirection();
	XMVECTOR GetAmbientColor();

private:
	XMVECTOR m_diffuseColor;
	XMVECTOR m_direction;
	XMVECTOR m_ambientColor;
};

#endif