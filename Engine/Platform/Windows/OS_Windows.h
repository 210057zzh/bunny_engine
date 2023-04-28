#pragma once
#include "MyWin.h"

#include "Engine/Platform/OS.h"


class OS_Windows : public OS
{
public:
	OS_Windows();
	~OS_Windows() override;
	void SetResolution(int width, int height) override;
	void InitializeWindow() override;

private:

	static LRESULT CALLBACK HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HINSTANCE m_hinstance_;
};
