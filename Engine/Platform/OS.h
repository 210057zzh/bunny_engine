#pragma once
class OS
{
public:
	virtual ~OS() = 0;
	virtual void SetResolution(int width, int height) = 0;
	virtual void InitializeWindow() = 0;
};

