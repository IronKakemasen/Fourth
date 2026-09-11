#include "WindowContext.h"
#include "WindowContextBuilder/WindowContextBuilder.h"
#include "WindowContextDiplomat/WindowContextToolLender/WindowContextToolLender.h"
#include "WindowContextDiplomat/WindowContextDiplomat.h"
#include "WindowContextDiplomat/WindowContextExecutionAgent/WindowContextExecutionAgent.h"

namespace
{
	auto const fileName = "WindowContext.cpp";
}

LRESULT CALLBACK WindowContext::WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_)
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

WindowContext::WindowContext(NexusFieldProof proof_)
{
	Logger::Entry("WindowContext: Constructor");

	//コアパーツを生成
	coreParts = Builder::Build(proof_);

	diplomat.reset
	(
		new WindowContextDiplomat
		(
			proof_,
			std::make_unique<ToolLender>(proof_, coreParts.hWnd),
			std::make_unique<ExecutionAgent>(proof_, *this)

		)
	);
	Logger::Log("Instantiate: Diplomat", fileName);
	Logger::Log("Instantiate: ToolLender", fileName);

	Logger::End("WindowContext: Constructor");

}

WindowContext::~WindowContext()
{

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowContext::Finalize(NexusFieldProof proof_, AgentKey agentKey_)
{
	if (coreParts.hWnd)
	{
		DestroyWindow(coreParts.hWnd);
		coreParts.hWnd = nullptr;
	}
	Logger::Log("DestroyWindow", fileName);

	//ウィンドウの登録を解除
	if (coreParts.hInst)
	{
		UnregisterClass(coreParts.windowName, coreParts.hInst);
	}
	Logger::Log("Unregister window", fileName);

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
