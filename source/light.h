#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <DirectXMath.h>

using namespace DirectX;

class Light
{
public:
	Light();
	~Light();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	XMVECTOR GetDiffuseColor();
	XMVECTOR GetDirection();

private:
	XMVECTOR m_diffuseColor;
	XMVECTOR m_direction;
};

#endif