#pragma once
#include "../SceneContext.h"

class SceneContextDiplomat
{
public:

	SceneContextDiplomat
	(
		SceneContext::NexusFieldProof proof_,
		std::unique_ptr<SceneContext::ExecutionAgent>&& executionAgent_
	);

	template<typename ToolType>
	auto& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}

	
private:


	std::tuple<std::unique_ptr<SceneContext::ExecutionAgent>> tools;

};

