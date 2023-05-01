#pragma once

class Graphics {
public:
	Graphics(int width, int height);
	void SetResolution(int width, int height);

private:
	int m_width;
	int m_height;
};
