#include "Graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Shader = 0;
}

Graphics::Graphics(const Graphics& other)
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new D3D();
	if (!m_D3D)
	{
		return false;
	}

	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	m_Camera = new ZCamera();
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	m_Model = new ZModel();
	result = m_Model->Initialize(m_D3D->GetDevice());

	m_Shader = new ZShader();
	result = m_Shader->Initialize(m_D3D->GetDevice(), hwnd);

	return true;
}

void Graphics::Shutdown()
{
	if(m_Shader)
	{
		m_Shader->Shutdown();
		delete m_Shader;
		m_Shader = 0;
	}

	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool Graphics::Frame()
{
	bool result;

	result = Render();
	if (!result)
		return false;

	return true;
}

bool Graphics::Render()
{
	bool result;
	D3DMATRIX worldMatrix, projectionMatrix;
	XMMATRIX xViewMatrix, xProjectionMatrix, xWorldMatrix;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();
	m_Camera->GetViewMatrix(xViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	for(int i = 0; i <4 ; i++)
	{
		xWorldMatrix.r[i] = XMVectorSet(worldMatrix.m[i][0], worldMatrix.m[i][1], worldMatrix.m[i][2], worldMatrix.m[i][3]);
		xProjectionMatrix.r[i] = XMVectorSet(projectionMatrix.m[i][0], projectionMatrix.m[i][1], projectionMatrix.m[i][2], projectionMatrix.m[i][3]);
	}
	
	m_Model->Render(m_D3D->GetDeviceContext());
	result = m_Shader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), xWorldMatrix, xViewMatrix, xProjectionMatrix);
	if (!result)
		return false;

	m_D3D->EndScene();

	return true;
}