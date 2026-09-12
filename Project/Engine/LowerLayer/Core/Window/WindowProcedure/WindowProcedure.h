#pragma once
#include "../WindowContext.h"

class WindowContext::WindowProcedure
{
	friend class WindowContext::Builder;
	static LRESULT CALLBACK WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_);
};

