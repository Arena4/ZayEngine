#include "WindowView.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	bool result;
	WindowView* System = new WindowView;

	if(!System) return 0;

	result = System->Initialize();
	if(result) System->Run();

	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}