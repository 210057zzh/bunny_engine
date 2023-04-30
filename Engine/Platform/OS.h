#pragma once
class OS
{
public:
	OS() = default;
	virtual ~OS() = default;
	virtual void SetResolution(int width, int height) = 0;
	virtual void InitializeWindow() = 0;
	virtual int Loop() = 0;

	OS(const OS& os) = delete;
	OS(OS&& os) = delete;
	OS& operator=(const OS& os) = delete;
	OS& operator=(OS&& os) = delete;
};

