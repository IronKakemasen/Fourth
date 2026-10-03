#pragma once
#include "../SwapChainContext.h"



class SwapChainContextDiplomat
{
public:

	SwapChainContextDiplomat
	(
		SwapChainContext::NexusFieldProof proof_,
		std::unique_ptr<SwapChainContext::ToolLender>&& toolLender_,
		std::unique_ptr<SwapChainContext::ExecutionAgent>&& executionAgent_

	);

	template<typename ToolType>
	auto& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}

private:

	std::tuple
	<
		std::unique_ptr<SwapChainContext::ToolLender>,
		std::unique_ptr<SwapChainContext::ExecutionAgent>
	> tools;

};