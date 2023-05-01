#include "OSWindows.h"
#include <comdef.h>
#include <iostream>
#include <sstream>

OsWindows::OsWindows() :
		OS(),
		m_hinstance(GetModuleHandle(nullptr)) {
}

OsWindows::~OsWindows() { DestroyWindow(m_hwnd); }

void OsWindows::SetResolution(const int width, const int height) {
	RECT rec;
	rec.left = 100;
	rec.right = width;
	rec.top = 100;
	rec.bottom = height;
	AdjustWindowRect(&rec, WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, FALSE);

	SetWindowPos(m_hwnd, nullptr, rec.left, rec.top, rec.right - rec.left,
			rec.bottom - rec.top, 0);
}

void OsWindows::InitializeWindow() {
	const auto p_class_name = "bunny_engine_window";
	// register window class
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessage;
	wc.hInstance = m_hinstance;
	wc.lpszClassName = p_class_name;
	RegisterClassEx(&wc);

	// create window
	m_hwnd = CreateWindowEx(0, p_class_name, "bunny_engine",
			WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, 0, 0, 10,
			10, nullptr, nullptr, m_hinstance, nullptr);

	ShowWindow(m_hwnd, SW_SHOW);
}

int OsWindows::Loop() {
	constexpr UINT messageBoxType = MB_OK | MB_ICONEXCLAMATION;
	try {
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (gResult == -1) {
			return -1;
		}
		return msg.wParam;
	} catch (const Exception &e) {
		MessageBox(nullptr, e.what(), e.GetType(), messageBoxType);
	} catch (...) {
		MessageBox(nullptr, "Unknown Exception", "Unknown Exception",
				messageBoxType);
	}
	return 0;
}

void OsWindows::ProcessMessage() {
	MSG msg;
	bool running = true;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		std::cout << "here";
		switch (msg.message) {
			case WM_KEYDOWN: {
				const auto param = static_cast<uint32_t>(msg.wParam);
				EventServer<OsKeyBoardEvent>::GetInstance().Notify(
						{ OsKeyBoardEvent::Type::Keydown, param });
			} break;
			case WM_KEYUP: {
				const auto param = static_cast<uint32_t>(msg.wParam);
				EventServer<OsKeyBoardEvent>::GetInstance().Notify(
						{ OsKeyBoardEvent::Type::Keyup, param });
			} break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

OsWindows::OsWindowsException::OsWindowsException(const int line, const char *file,
		const HRESULT hr) noexcept :
		Exception(line, file),
		m_hr(hr) {
}

const char *OsWindows::OsWindowsException::what() const noexcept {
	std::ostringstream oss;
	oss << GetType() << '\n'
		<< "Error Code:" << GetErrorCode() << '\n'
		<< GetErrorString() << "From:" << GetThrowLocationString() << '\n';
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char *OsWindows::OsWindowsException::GetType() const noexcept {
	return "OS Windows Exception";
}

std::string OsWindows::OsWindowsException::TranslateErrorCode(const HRESULT hr) noexcept {
	const _com_error err(hr);
	const LPCTSTR errMsg = err.ErrorMessage();
	return std::string{ errMsg };
}

HRESULT OsWindows::OsWindowsException::GetErrorCode() const noexcept { return m_hr; }

std::string OsWindows::OsWindowsException::GetErrorString() const noexcept {
	return TranslateErrorCode(m_hr);
}

LRESULT OsWindows::HandleMessage(const HWND hwnd, const UINT uMsg, const WPARAM wParam,
		const LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			EventServer<OsKeyBoardEvent>::GetInstance().Notify(
					{ OsKeyBoardEvent::Type::Keydown, VK_ESCAPE });
			break;
		default:
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
