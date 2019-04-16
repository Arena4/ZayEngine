#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <windows.h>
#include "d3d.h"
#include "camera.h"
#include "model.h"
#include "shader.h"

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
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	D3D* m_D3D;
	ZModel* m_Model;
	ZCamera* m_Camera;
	ZShader* m_Shader;
};

#endif