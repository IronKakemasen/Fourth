#pragma once

class WinApp;

class WindowContext
{
public:

	struct AccessKey
	{
	private:
		friend class WinApp;
		explicit AccessKey() = default;
	};

	WindowContext(AccessKey accessKey_, uint32_t width_, uint32_t height_, LPCWSTR windowName_);
	void Finalize(AccessKey accessKey_);

private:

	struct Param
	{
		HINSTANCE m_hInst;
		HWND m_hWnd;
		uint32_t m_width;
		uint32_t m_height;
		LPCWSTR m_windowName;
	};

	Param setupParam;
	static LRESULT CALLBACK WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_);
};

//例外登録関数
LONG WINAPI ExportDump(EXCEPTION_POINTERS* exception);


