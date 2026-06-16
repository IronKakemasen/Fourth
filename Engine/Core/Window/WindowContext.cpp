#include "WindowContext.h"
#include <strsafe.h>
#include "../../WinApp/WinApp.h"
#include "DumpExporter.h"

LRESULT CALLBACK WindowContext::WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_)
{
#ifdef USE_IMGUI
	//ImGuiにメッセージを渡す
	if (ImGui_ImplWin32_WndProcHandler(hWnd_, msg_, wParam_, lParam_))
	{
		return true;
	}
#endif

	//メッセージに応じてゲーム固有の処理を行う
	switch (msg_)
	{
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);

		return 0;
	}

	//標準メッセージの処理を行う
	return DefWindowProc(hWnd_, msg_, wParam_, lParam_);
}


void WindowContext::Finalize()
{
	//ウィンドウの登録を解除
	if (setupParam.m_hInst)
	{
		UnregisterClass(setupParam.m_windowName, setupParam.m_hInst);
	}

	setupParam.m_hInst = nullptr;
	setupParam.m_hWnd = nullptr;
}

HWND WindowContext::WatchHWND()
{
	return setupParam.m_hWnd;
}


WindowContext::WindowContext(InstacnceKey instanceKey_)
{
	using namespace ProjectConfig::Window;

	auto hInst = GetModuleHandle(nullptr);

	assert(!(!hInst) && "hInstがぬるぽ");

	// ウィンドウクラスの登録
	WNDCLASSEX wc = {};

	setupParam.m_windowName = kTitle;
	setupParam.m_width = (uint32_t)kWidth;
	setupParam.m_height = (uint32_t)kHeight;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowContext::WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = kTitle;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	//ウィンドウの登録
	ErrorMessageOutput::Abort::DetectError(RegisterClassEx(&wc), "ウィンドウの登録失敗", "WindowContext.cpp");

	//インスタンスハンドルの設定
	setupParam.m_hInst = hInst;

	//WindowSize
	RECT rc = {};
	rc.right = static_cast<LONG>(setupParam.m_width);
	rc.bottom = static_cast<LONG>(setupParam.m_height);
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// ウィンドウの作成
	setupParam.m_hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		kTitle,                   // Window class
		kTitle,					// Window text
		style,							// Window style
		// Size and position
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,							// Parent window    
		nullptr,							// Menu
		setupParam.m_hInst,						// Instance handle
		nullptr							// Additional application data
	);

	ErrorMessageOutput::Abort::DetectError((setupParam.m_hWnd != NULL), "m_hWndがぬるぽ","WindowContext.cpp");

	// ウィンドウの表示
	if(setupParam.m_hWnd != 0 ) ShowWindow(setupParam.m_hWnd, SW_SHOWNORMAL);

	//ウィンドウにフォーカスを設定
	SetFocus(setupParam.m_hWnd);

	//入力インターフェースの初期化
	//inputInterface.Initialize(m_hInst, m_hWnd);

	//誰も捕捉しなかった場合に(Unhandled)、補足する関数を登録
	SetUnhandledExceptionFilter(ExportDump);


}



