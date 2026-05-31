#include "Engine/Debug/RuntimeDebugger/RuntimeDebugger.h"
#include "Engine/WinApp/WinApp.h"

//プロジェクトの設定がつまってる
using namespace ProjectConfig;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//デバッガー。kDebugLayer,kPointerValidator,kLeakChecker
	RuntimeDebugger runtimeDebugger({Debug::k0EnableDebugLayer,Debug::k1EnablePointerValidator, Debug::k2EnableLeakChecker});

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