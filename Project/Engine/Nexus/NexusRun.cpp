#include "Nexus.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/SwapChain/SwapChainContextDiplomat/SwapChainContextDiplomat.h"
#include "../LowerLayer/Core/SwapChain/SwapChainContextDiplomat/SwapChainExecutionAgent/SwapChainExecutionAgent.h"
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../LowerLayer/Core/Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../LowerLayer/Core/Command/CommandContextDiplomat/CommandContextExecutionAgent/CommandContextExecutionAgent.h"


void Nexus::Run(aFourthProof proof_)
{
	//SwapChainContextの代行クラス
	auto& s_ExecutionAgent = swapChainContext->AccessDiplomat().Access<SwapChainContext::ExecutionAgent>();
	//CommandContextの代行クラス
	auto& c_ExecutionAgent = commandContext->AccessDiplomat().Access<CommandContext::ExecutionAgent>();


	auto const frameIndex = s_ExecutionAgent.GetFrameIndex(SwapChainContext::NexusFieldProof{});



	//コマンドの記録開始
	c_ExecutionAgent.StartRecordingCommands(CommandContext::NexusFieldProof{}, frameIndex);




	//コマンドを送る
	c_ExecutionAgent.ExecuteCommands(CommandContext::NexusFieldProof{},frameIndex);


	//表示
	s_ExecutionAgent.Present(SwapChainContext::NexusFieldProof{});
}
