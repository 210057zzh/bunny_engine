#pragma once
#include "Engine/Platform/OS.h"
#include "Engine/Util/EventServer.h"
#include "Engine/Util/Exception.h"
#include "MyWin.h"

class OsWindows : public OS {
public:
	OsWindows();
	~OsWindows() override;
	OsWindows(const OsWindows &os) = delete;
	OsWindows(OsWindows &&os) = delete;
	OsWindows &operator=(const OsWindows &os) = delete;
	OsWindows &operator=(OsWindows &&os) = delete;

	void SetResolution(int width, int height) override;
	void InitializeWindow() override;
	int Loop() override;
	void ProcessMessage() override;

	class OsWindowsException : public Exception {
	public:
		OsWindowsException(int line, const char *file, HRESULT hr) noexcept;
		const char *what() const noexcept override;
		const char *GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;

	private:
		HRESULT m_hr;
	};

private:
	static LRESULT CALLBACK HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND m_hwnd{ nullptr };
	HINSTANCE m_hinstance;
};

#define WINDOWS_EXCEPTION(hr) OSWindows::OsWindowsException(__LINE__, __FILE__, hr)
#define GET_LAST_ERROR() OSWindows::OsWindowsException(__LINE__, __FILE__, GetLastError())
