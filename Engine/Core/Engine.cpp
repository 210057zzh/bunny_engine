#include "Engine.h"
#include "Engine/Platform/Windows/OSWindows.h"
#include "Graphics/Graphics.h"

Engine Engine::s_instance_;

Engine::Engine()
{
}

void Engine::Init(int width, int height, std::unique_ptr<OS>&& system)
{
	os = std::move(system);
	graphics = std::make_unique<Graphics>(width, height);
	graphics->SetResolution(width, height);
}

int Engine::Loop()
{
	return os->Loop();
}

Engine& Engine::GetInstance()
{
	return s_instance_;
}
