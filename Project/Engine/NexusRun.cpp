#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/SwapChain/Presenter/Presenter.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LowerLayer/Core/Command/RuntimeCommandControler/RuntimeCommandControler.h"


void Nexus::Run()
{
	auto const frameIndex = swapChainContext->presenter->GetFrameIndex();
	static auto* runtimeCmdControler = commandContext->runtimeCommandControler.get();
	static auto* presenter = swapChainContext->presenter.get();


	//コマンドの記録開始
	runtimeCmdControler->RecordingStart(frameIndex);




	//コマンドを送る
	runtimeCmdControler->ExecuteCommands(frameIndex);


	//表示
	presenter->Present();
}
