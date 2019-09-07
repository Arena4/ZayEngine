#include "camera.h"

ZCamera::ZCamera()
{
	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;
	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;
}

ZCamera::~ZCamera()
{
}

void ZCamera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}

void ZCamera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}

XMVECTOR ZCamera::GetPosition()
{
	return {m_positionX, m_positionY, m_positionZ};
}

XMVECTOR ZCamera::GetRotation()
{
	return {m_rotationX, m_rotationY, m_rotationZ};
}

void ZCamera::Render()
{
	float yaw, pitch, roll;
	XMVECTOR up, position, lookAt;
	XMMATRIX rotationMatrix;

	position = XMVectorSet(m_positionX, m_positionY, m_positionZ, 0);
	up = XMVectorSet(0, 1, 0, 0);
	lookAt = XMVectorSet(0, 0, 1, 0);

	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;	

	rotationMatrix = XMMatrixRotationRollPitchYaw(roll, pitch, yaw);
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	lookAt = position + lookAt;

	m_viewMatrix= XMMatrixLookAtLH(position, lookAt, up);
}

void ZCamera::GetViewMatrix(XMMATRIX & viewMatrix)
{
	viewMatrix = m_viewMatrix;
}
