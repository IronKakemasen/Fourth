#include "Engine/WinApp/WinApp.h"

using namespace ProjectConfig;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//＜ポインタ破壊などを検知するためのもの＞
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);

	WinApp winApp((UINT)kWindowWidth, (UINT)kWindowHeight, kWindowTitle);

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