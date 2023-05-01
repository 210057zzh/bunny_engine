#pragma once
#include "MyWin.h"
#include "Engine/Platform/OS.h"
#include "Engine/Util/EventServer.h"
#include "Engine/Util/Exception.h"


class OSWindows : public OS
{
public:
	OSWindows();
	~OSWindows() override;
	OSWindows(const OSWindows& os) = delete;
	OSWindows(OSWindows&& os) = delete;
	OSWindows& operator=(const OSWindows& os) = delete;
	OSWindows& operator=(OSWindows&& os) = delete;

	void SetResolution(int width, int height) override;
	void InitializeWindow() override;
	int Loop() override;
	void ProcessMessage() override;


	class OSException : public Exception
	{
	public:
		OSException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		char const* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT m_hr_;
	};



private:
	static LRESULT CALLBACK HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND m_hwnd_{ nullptr };
	HINSTANCE m_hinstance_;
};

#define WINDOWS_EXCEPTION(hr) OSWindows::OSException(__LINE__, __FILE__, hr)
#define GET_LAST_ERROR() OSWindows::OSException(__LINE__, __FILE__, GetLastError())
