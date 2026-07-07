#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/SwapChain/Presenter/Presenter.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/Command/RuntimeCommandController/RuntimeCommandController.h"


void Nexus::Run()
{
	auto const frameIndex = swapChainContext->presenter->GetFrameIndex();
	static auto* runtimeCmdController = commandContext->runtimeCommandController.get();
	static auto* presenter = swapChainContext->presenter.get();


	//コマンドの記録開始
	runtimeCmdController->RecordingStart(frameIndex);




	//コマンドを送る
	runtimeCmdController->ExecuteCommands(frameIndex);


	//表示
	presenter->Present();
}
