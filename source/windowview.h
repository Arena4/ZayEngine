#ifndef _WINDOWVIEW_H_
#define _WINDOWVIEW_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "Input.h"
#include "Graphics.h"

class WindowView
{
public:
	WindowView();
	WindowView(const WindowView&);
	~WindowView();

	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	Input* m_Input;
	Graphics* m_Graphics;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static WindowView* ApplicationHandle = 0;
#endif