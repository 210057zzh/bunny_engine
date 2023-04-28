#include "OS_Windows.h"

OS_Windows::OS_Windows() : m_hinstance_(GetModuleHandle(nullptr))
{

}

OS_Windows::~OS_Windows()
{
}

void OS_Windows::SetResolution(int width, int height)
{
}

void OS_Windows::InitializeWindow()
{
	const auto pClassName = L"bunny_engine_window";
	// register window class
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessage;
	wc.hInstance = m_hinstance_;
	wc.lpszClassName = pClassName;
	RegisterClassEx(&wc);

	// create window
	const auto hWindow = CreateWindowEx(
		0,
		pClassName,
		L"bunny_engine",
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU,
		0,
		0,
		10,
		10,
		nullptr,
		nullptr,
		m_hinstance_,
		nullptr);

	ShowWindow(hWindow, SW_SHOW);
}

LRESULT OS_Windows::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hwnd, L"bunny_window");
		}
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hwnd, L"bunny_f_window");
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
