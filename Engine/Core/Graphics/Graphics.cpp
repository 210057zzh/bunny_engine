#include "Graphics.h"

#include "Engine/Core/Engine.h"
#include "Engine/Platform/OS.h"


Graphics::Graphics(int width, int height) : m_width_(width), m_height_(height)
{
	Engine::GetInstance().os->InitializeWindow();
	Engine::GetInstance().os->SetResolution(width, height);
}

void Graphics::SetResolution(int width, int height)
{
	m_width_ = width;
	m_height_ = height;
	Engine::GetInstance().os->SetResolution(width, height);
}

