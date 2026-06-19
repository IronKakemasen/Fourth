#include "Nexus.h"
#include "../Core/SwapChain/Presenter/Presenter.h"
#include "../Core/Command/CommandExecutor/CommandExecutor.h"

void Nexus::Run()
{
	auto const frameIndex = swapChainContext->presenter->GetFrameIndex();

	//コマンドの記録開始
	commandContext->RecordingStart(frameIndex);




	//コマンドを送る
	commandContext->ExecuteCommands(frameIndex);

	//表示
	swapChainContext->presenter->Present();
}
