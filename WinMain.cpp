#include <Windows.h>

#include "Engine/Core/Engine.h"
#include "Engine/Platform/Windows/OSWindows.h"

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
