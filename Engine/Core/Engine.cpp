#include "Engine.h"
#include "Engine/Platform/Windows/OS_Windows.h"
#include "Graphics/Window.h"

Engine::Engine(int width, int height)
	: window(new Window(width, height)), os(new OS_Windows())
{
}

const Engine& Engine::GetInstance()
{
	return s_instance_;
}
