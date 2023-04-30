#include "OSWindows.h"
#include <comdef.h>
#include <sstream>

OSWindows::OSWindows() : OS(), m_hinstance_(GetModuleHandle(nullptr))
{
}

OSWindows::~OSWindows()
{
	DestroyWindow(m_hwnd_);
}

void OSWindows::SetResolution(int width, int height)
{
	RECT rec;
	rec.left = 100;
	rec.right = width;
	rec.top = 100;
	rec.bottom = height;
	AdjustWindowRect(&rec, WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, FALSE);

	SetWindowPos(m_hwnd_, nullptr, rec.left, rec.top, rec.right - rec.left, rec.bottom - rec.top, 0);
}

void OSWindows::InitializeWindow()
{
	const auto pClassName = "bunny_engine_window";
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
	m_hwnd_ = CreateWindowEx(
		0,
		pClassName,
		"bunny_engine",
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU,
		0,
		0,
		10,
		10,
		nullptr,
		nullptr,
		m_hinstance_,
		nullptr);

	ShowWindow(m_hwnd_, SW_SHOW);
}

int OSWindows::Loop()
{
	UINT messageBoxType = MB_OK | MB_ICONEXCLAMATION;
	try
	{
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
		return msg.wParam;
	}
	catch (const Exception& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), messageBoxType);
	}
	catch (...)
	{
		MessageBox(nullptr, "Unknown Exception", "Unknown Exception", messageBoxType);
	}
}

OSWindows::OSException::OSException(int line, const char* file, HRESULT hr) noexcept
	:Exception(line, file), m_hr_(hr)
{
}

const char* OSWindows::OSException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << '\n'
		<< "Error Code:" << GetErrorCode() << '\n'
		<< GetErrorString()
		<< "From:" << GetThrowLocationString()
		<< '\n';
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

char const* OSWindows::OSException::GetType() const noexcept
{
	return "OS Windows Exception";
}

std::string OSWindows::OSException::TranslateErrorCode(HRESULT hr) noexcept
{
	_com_error err(hr);
	LPCTSTR errMsg = err.ErrorMessage();
	return std::string(errMsg);
}

HRESULT OSWindows::OSException::GetErrorCode() const noexcept
{
	return m_hr_;
}

std::string OSWindows::OSException::GetErrorString() const noexcept
{
	return TranslateErrorCode(m_hr_);
}

LRESULT OSWindows::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hwnd, "bunny_window");
		}
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hwnd, "bunny_f_window");
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
