#pragma once
#include "../MeshContext.h"

class MeshContextDiplomat
{
public:

	MeshContextDiplomat
	(
		MeshContext::NexusFieldProof proof_,
		std::unique_ptr<MeshContext::ExecutionAgent>&& agent_
	);
	
	template<typename ToolType>
	auto* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();

	}

private:

	std::tuple<std::unique_ptr<MeshContext::ExecutionAgent>> tools;
};

