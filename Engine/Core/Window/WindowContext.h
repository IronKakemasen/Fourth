#pragma once

class Nexus;

class WindowContext
{
public:

	struct InstacnceKey;

	WindowContext(InstacnceKey instanceKey_);
	void Finalize();
	HWND WatchHWND();

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


struct WindowContext::InstacnceKey
{
private:
	friend class Nexus;
	explicit InstacnceKey() = default;
};
