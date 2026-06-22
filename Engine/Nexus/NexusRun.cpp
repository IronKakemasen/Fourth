#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../Core/SwapChain/Presenter/Presenter.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../Core/Command/RuntimeCommandControler/RuntimeCommandControler.h"


void Nexus::Run()
{
	auto const frameIndex = swapChainContext->presenter->GetFrameIndex();
	auto* runtimeCmdControler = commandContext->runtimeCommandControler.get();
	auto* presenter = swapChainContext->presenter.get();


	//コマンドの記録開始
	runtimeCmdControler->RecordingStart(frameIndex);




	//コマンドを送る
	runtimeCmdControler->ExecuteCommands(frameIndex);


	//表示
	presenter->Present();
}
