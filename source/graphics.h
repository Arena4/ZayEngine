#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "d3d.h"
#include "camera.h"
#include "model.h"
#include "shader.h"
#include "texture.h"
#include "light.h"
#include "light_shader.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	
	Graphics(const Graphics&);
	
	~Graphics();
	
	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	
	bool Frame();

	void Shutdown();
	
private:

	bool Render(float);

private:
	D3D* m_D3D;
	
	ZModel* m_Model;
	
	ZCamera* m_Camera;
	
	ZShader* m_Shader;
	
	ZTexture* m_Texture;
	
	ZLight* m_Light;
	
	ZLightShader* m_LightShader;
};

#endif