#pragma once
#include "./Core/Window/WindowContext.h"

class WinApp
{
public:

	~WinApp();
	WinApp(uint32_t width_, uint32_t height_, LPCWSTR windowName_);

	WinApp(const WinApp&) = delete;
	WinApp& operator=(const WinApp&) = delete;
	WinApp(WinApp&&) = delete;
	WinApp& operator=(WinApp&&) = delete;

private:

	//[ 前方宣言 ] WinAppのインスタンスを1つに制限するためのシングルトンクラス
	class InstanceLimiter;

	//ウィンドウを制御するもの
	std::unique_ptr<WindowContext> windowContext;

};

