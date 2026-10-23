#pragma once
#include "../RenderContext.h"

class RenderContextDiplomat
{
public:

	RenderContextDiplomat
	(
		RenderContext::NexusFieldProof proof_,
		std::unique_ptr<RenderContext::ExecutionAgent>&& agent_
	);

	template<typename ToolType>
	auto& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}

private:

	std::tuple<std::unique_ptr<RenderContext::ExecutionAgent>> tools;

};

