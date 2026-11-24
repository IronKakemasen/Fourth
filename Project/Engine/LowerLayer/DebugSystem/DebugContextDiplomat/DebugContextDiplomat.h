#pragma once
#include "../DebugContext.h"

class DebugContextDiplomat
{
public:

	DebugContextDiplomat
	(
		DebugContext::NexusFieldProof proof_,
		std::unique_ptr<DebugContext::ExecutionAgent>&& executionAgent_
	);

	~DebugContextDiplomat();

	template<typename ToolType>
	auto& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}

private:

	std::tuple
	<
		std::unique_ptr<DebugContext::ExecutionAgent>
	>tools;

};

