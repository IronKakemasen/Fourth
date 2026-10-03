#include "PreCompileHeader.h"
#include "SwapChainContextDiplomat.h"
#include "SwapChainContextToolLender/SwapChainContextToolLender.h"
#include "SwapChainExecutionAgent/SwapChainExecutionAgent.h"

SwapChainContextDiplomat::SwapChainContextDiplomat
(
	SwapChainContext::NexusFieldProof proof_,
	std::unique_ptr<SwapChainContext::ToolLender>&& toolLender_,
	std::unique_ptr<SwapChainContext::ExecutionAgent>&& executionAgent_
)
{
	std::get<std::unique_ptr<SwapChainContext::ToolLender>>(tools) = std::move(toolLender_);
	std::get<std::unique_ptr<SwapChainContext::ExecutionAgent>>(tools) = std::move(executionAgent_);

}
