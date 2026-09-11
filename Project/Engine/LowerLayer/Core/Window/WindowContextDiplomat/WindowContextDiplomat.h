#pragma once
#include "../WindowContext.h"

class WindowContextDiplomat
{
public:

	WindowContextDiplomat
	(
		WindowContext::NexusFieldProof proof_,
		std::unique_ptr<WindowContext::ToolLender>&& toolLender_,
		std::unique_ptr<WindowContext::ExecutionAgent>&& executionAgent_
	);

	template<typename ToolType>
	ToolType& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}

private:

	std::tuple
	<
		std::unique_ptr<WindowContext::ToolLender>,
		std::unique_ptr<WindowContext::ExecutionAgent>
	> tools;

};


