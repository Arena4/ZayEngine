#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <directxmath.h>
using namespace DirectX;

class ZCamera
{
public:
	ZCamera();

	~ZCamera();
	
	void SetPosition(float x, float y, float z);
	
	void SetRotation(float x, float y, float z);
	
	void Render();
	
	void GetViewMatrix(XMMATRIX& viewMatrix);
	
	XMVECTOR GetPosition();
	
	XMVECTOR GetRotation();

private:
	float m_positionX, m_positionY, m_positionZ;
	
	float m_rotationX, m_rotationY, m_rotationZ;
	
	XMMATRIX m_viewMatrix;
};

#endif