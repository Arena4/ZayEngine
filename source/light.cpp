#include "light.h"

Light::Light()
{
}

Light::~Light()
{
}

void Light::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMVectorSet(red, green, blue, alpha);
}

void Light::SetDirection(float x, float y, float z)
{
	m_direction = XMVectorSet(x, y, z, 0);
}

XMVECTOR Light::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMVECTOR Light::GetDirection()
{
	return m_direction;
}
