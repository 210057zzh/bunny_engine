#include <Windows.h>

#include "Engine/Core/Engine.h"
#include "Engine/Platform/Windows/OSWindows.h"

// Indicates to hybrid graphics systems to prefer the discrete part by default
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	Engine::GetInstance().Init(1280, 720, std::make_unique<OSWindows>());
	Engine::GetInstance().Loop();

	return 0;
}
