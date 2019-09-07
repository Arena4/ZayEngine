#include "graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Shader = 0;
	m_Texture = 0;
	m_LightShader = 0;
	m_Light = 0;
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
	result = m_Model->Initialize(m_D3D->GetDevice(), "data/cube.txt", L"data/seafloor.dds");

	m_Shader = new ZShader();
	result = m_Shader->Initialize(m_D3D->GetDevice(), hwnd);

	m_LightShader = new LightShader();
	m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);

	m_Light = new Light();
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 0.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, 0.0f, 0.0f);

	return true;
}

void Graphics::Shutdown()
{
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if(m_LightShader)
	{
		delete m_LightShader;
		m_LightShader = 0;
	}

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
	static float rotation = 0.0f;
	rotation += (float)3.14159f * 0.005f;
	if (rotation > 360.0f)
		rotation -= 360.0f;

	result = Render(rotation);
	if (!result)
		return false;

	return true;
}

bool Graphics::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	float bgColor = 30.0f / 255;
	m_D3D->BeginScene(bgColor, bgColor, bgColor, bgColor);

	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	
	worldMatrix = worldMatrix * XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor() ,m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}