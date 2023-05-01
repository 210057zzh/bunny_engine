#include "Graphics.h"

#include "Engine/Core/Engine.h"
#include "Engine/Platform/OS.h"

Graphics::Graphics(const int width, const int height) :
		m_width(width),
		m_height(height) {
	Engine::GetInstance().os->InitializeWindow();
	Engine::GetInstance().os->SetResolution(width, height);
}

void Graphics::SetResolution(const int width, const int height) {
	m_width = width;
	m_height = height;
	Engine::GetInstance().os->SetResolution(width, height);
}
