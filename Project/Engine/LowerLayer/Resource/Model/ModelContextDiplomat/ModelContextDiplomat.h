#pragma once
#include "../ModelContext.h"

class ModelContextDiplomat
{
public:

	ModelContextDiplomat
	(
		ModelContext::NexusFieldProof proof_,
		std::unique_ptr<ModelContext::ExecutionAgent>&& agent_,
		std::unique_ptr<ModelContext::ToolLender>&& toolLender_,
		std::unique_ptr<ModelContext::CommandProvider>&& cmdProvider_ 


	);
	
	template<typename ToolType>
	auto* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}

private:

	std::tuple
	<
		std::unique_ptr<ModelContext::ExecutionAgent>,
		std::unique_ptr<ModelContext::ToolLender>,
		std::unique_ptr<ModelContext::CommandProvider>

	> tools;
};

