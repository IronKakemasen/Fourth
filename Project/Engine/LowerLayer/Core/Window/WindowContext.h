#pragma once

class Nexus;

class WindowContext
{
public:

	struct InstanceKey;

	WindowContext(InstanceKey instanceKey_);
	void Finalize();
	HWND WatchHWND();

private:

	struct Param
	{
		HINSTANCE m_hInst;
		HWND m_hWnd;
		UINT m_width;
		UINT m_height;
		LPCWSTR m_windowName;
	};

	Param setupParam;
	static LRESULT CALLBACK WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_);
};


struct WindowContext::InstanceKey
{
private:
	friend class Nexus;
	explicit InstanceKey() = default;
};
