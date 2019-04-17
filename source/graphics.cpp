#include "graphics.h"

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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDevice());

	// Render the model using the color shader.
	result = m_Shader->Render(m_D3D->GetDevice(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}