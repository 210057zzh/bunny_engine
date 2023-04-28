#pragma once

class Window
{
public:
	Window(int width, int height);
	void ResizeWindow(int width, int height);

private:
	int m_width_;
	int m_height_;
};
