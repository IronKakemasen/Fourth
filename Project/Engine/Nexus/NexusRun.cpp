#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/SwapChain/SwapChainContextDiplomat/SwapChainContextDiplomat.h"
#include "../LowerLayer/Core/SwapChain/SwapChainContextDiplomat/SwapChainExecutionAgent/SwapChainExecutionAgent.h"

#include "../LowerLayer/Core/SwapChain/Presenter/Presenter.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/Command/RuntimeCommandController/RuntimeCommandController.h"


void Nexus::Run()
{
	//SwapChainContextの代行クラス
	auto& s_ExecutionAgent = swapChainContext->AccessDiplomat().Access<SwapChainContext::ExecutionAgent>();
	


	auto const frameIndex = s_ExecutionAgent.GetFrameIndex(SwapChainContext::NexusFieldProof{});

	auto* runtimeCmdController = commandContext->runtimeCommandController.get();


	//コマンドの記録開始
	runtimeCmdController->RecordingStart(frameIndex);




	//コマンドを送る
	runtimeCmdController->ExecuteCommands(frameIndex);


	//表示
	s_ExecutionAgent.Present(SwapChainContext::NexusFieldProof{});
}
