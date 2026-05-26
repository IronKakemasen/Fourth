#include <windows.h>
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	//＜ポインタ破壊などを検知するためのもの＞
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);


	return 0;
}