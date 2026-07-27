#pragma once
#include "../ModelContext.h"

class MeshContextDiplomat
{
public:

	MeshContextDiplomat
	(
		ModelContext::NexusFieldProof proof_,
		std::unique_ptr<ModelContext::ExecutionAgent>&& agent_
	);
	
	template<typename ToolType>
	auto* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}

private:

	std::tuple<std::unique_ptr<ModelContext::ExecutionAgent>> tools;
};

