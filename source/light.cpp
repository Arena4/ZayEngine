#include "light.h"

ZLight::ZLight()
{
}

ZLight::~ZLight()
{
}

void ZLight::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMVectorSet(red, green, blue, alpha);
}

void ZLight::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMVectorSet(red, green, blue, alpha);
}

void ZLight::SetDirection(float x, float y, float z)
{
	m_direction = XMVectorSet(x, y, z, 0);
}

XMVECTOR ZLight::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMVECTOR ZLight::GetDirection()
{
	return m_direction;
}

XMVECTOR ZLight::GetAmbientColor()
{
	return m_ambientColor;
}
