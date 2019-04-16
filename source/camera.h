#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <D3D11.h>
#include <DirectXMath.h>

using namespace DirectX;

class ZCamera
{
public:
	ZCamera();
	~ZCamera();
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	XMVECTOR GetPosition();
	XMVECTOR GetRotation();
	void Render();
	void GetViewMatrix(XMMATRIX& viewMatrix);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_viewMatrix;
};

#endif