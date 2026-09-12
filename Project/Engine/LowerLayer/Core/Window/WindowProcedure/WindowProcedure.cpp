#include "PreCompileHeader.h"
#include "WindowProcedure.h"

LRESULT CALLBACK WindowContext::WindowProcedure::WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_)
{
	//#ifdef USE_IMGUI
	//	//ImGuiにメッセージを渡す
	//	if (ImGui_ImplWin32_WndProcHandler(hWnd_, msg_, wParam_, lParam_))
	//	{
	//		return true;
	//	}
	//#endif

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
