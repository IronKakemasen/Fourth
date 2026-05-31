#include "Engine/WinApp/WinApp.h"
#include "Engine/Debug/RuntimeDebugger/RuntimeDebugger.h"

using namespace ProjectConfig;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//デバッガー。kDebugLayer,kPointerValidator,kLeakChecker
	RuntimeDebugger runtimeDebugger({Debug::kEnableDebugLayer,Debug::kEnablePointerValidator, Debug::kEnableDebugLayer});

	//アプリケーションクラス
	WinApp winApp((UINT)Window::kWidth, (UINT)Window::kHeight, Window::kTitle);

	MSG msg = {};

	while (WM_QUIT != msg.message)
	{
		//Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		}
	}

	return 0;
}