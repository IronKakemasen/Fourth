#include "WindowContext.h"
#include <strsafe.h>
#include "../../WinApp/WinApp.h"

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


WindowContext::WindowContext(CraftKey craftKey_, uint32_t width_, uint32_t height_, LPCWSTR windowName_)
{
//#ifdef _DEBUG
//
//	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
//	{
//		debugController->EnableDebugLayer();
//		debugController->SetEnableGPUBasedValidation(TRUE);
//	}
//
//#endif // _DEBUG

	auto hInst = GetModuleHandle(nullptr);

	assert(!(!hInst) && "hInstがぬるぽ");

	// ウィンドウクラスの登録
	WNDCLASSEX wc = {};

	setupParam.m_windowName = windowName_;
	setupParam.m_width = (uint32_t)width_;
	setupParam.m_height = (uint32_t)height_;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowContext::WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = windowName_;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	//ウィンドウの登録
	if (!RegisterClassEx(&wc))
	{
		assert(false && "ウィンドウの登録失敗");
	}

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
		windowName_,                   // Window class
		windowName_,					// Window text
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

	assert(!(setupParam.m_hWnd == NULL) && "m_hWndがぬるぽ");

	// ウィンドウの表示
	ShowWindow(setupParam.m_hWnd, SW_SHOWNORMAL);

	//ウィンドウにフォーカスを設定
	SetFocus(setupParam.m_hWnd);

	//入力インターフェースの初期化
	//inputInterface.Initialize(m_hInst, m_hWnd);

	//誰も捕捉しなかった場合に(Unhandled)、補足する関数を登録
	SetUnhandledExceptionFilter(ExportDump);


}

//例外登録関数
LONG WINAPI ExportDump(EXCEPTION_POINTERS* exception)
{
	//時刻を取得して、時刻を名前に入れたファイルを作成
	SYSTEMTIME time;
	GetLocalTime(&time);
	wchar_t filePath[MAX_PATH] = { 0 };
	CreateDirectory(L"./Dumps", nullptr);
	StringCchPrintfW(filePath, MAX_PATH, L"./Dumps/%04d-%02d%02d-%02d%02d.dmp",
		time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute);
	HANDLE dumpFileHandle = CreateFile(filePath, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
	//processID(このexeのID)とクラッシュの発生したthreadIDを取得
	DWORD processId = GetCurrentProcessId();
	DWORD threadId = GetCurrentThreadId();
	//設定情報を入力
	MINIDUMP_EXCEPTION_INFORMATION minidumpInformation{ 0 };
	minidumpInformation.ThreadId = threadId;
	minidumpInformation.ExceptionPointers = exception;
	minidumpInformation.ClientPointers = TRUE;
	//Dumpを出力。MiniDumpNormalは最低限の情報を出力するフラグ
	MiniDumpWriteDump(GetCurrentProcess(), processId, dumpFileHandle,
		MiniDumpNormal, &minidumpInformation, nullptr, nullptr);

	//他に関連付けられているSEHハンドラがあれば実行
	return EXCEPTION_EXECUTE_HANDLER;
}



