#include "Engine.h"
#include "Engine/Core/IO/KeyboardManager.h"
#include "Engine/Platform/Windows/OSWindows.h"
#include "Graphics/Graphics.h"

Engine Engine::s_instance_;

Engine::Engine()
{
	keyboard_manager_ = std::make_unique<KeyboardManager>();
}

void Engine::Init(int width, int height, std::unique_ptr<OS>&& system)
{
	os = std::move(system);
	graphics = std::make_unique<Graphics>(width, height);
	graphics->SetResolution(width, height);
}

int Engine::Loop()
{
	while (m_running_)
	{
		Frame();
	}
	return 0;
}

int Engine::Frame()
{
	os->ProcessMessage();
	if (keyboard_manager_->key_states[VK_ESCAPE])
	{
		Terminate();
	}
	return 0;
}

Engine& Engine::GetInstance()
{
	return s_instance_;
}
