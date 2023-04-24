#include <Windows.h>

const auto cWindowWidth = 1920;
const auto cWindowHeight = 1080;

LRESULT CALLBACK main_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	const auto pClassName = L"bunny_engine_window";
	// register window class
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = main_window_proc;
	wc.hInstance = hInstance;
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
		cWindowWidth,
		cWindowHeight,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	ShowWindow(hWindow, SW_SHOW);

	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
	return 0;
}

LRESULT main_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
