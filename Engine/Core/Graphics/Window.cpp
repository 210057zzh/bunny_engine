#include "Window.h"
#include "Engine/Core/Engine.h"
#include "Engine/Platform/OS.h"

Window::Window(int width, int height) : m_width_(width), m_height_(height)
{

}

void Window::ResizeWindow(int width, int height)
{
	m_width_ = width;
	m_height_ = height;
	Engine::GetInstance().os->SetResolution(width, height);
}
