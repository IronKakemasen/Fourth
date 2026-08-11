#pragma once
#include "../PSO_Context.h"

class PSO_ContextDiplomat
{
public:

	PSO_ContextDiplomat
	(
		PSO_Context::NexusFieldProof proof_,
		std::unique_ptr<PSO_Context::ToolLender>&& toolLender_
	);

	template<typename ToolType>
	auto* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}


private:

	std::tuple<std::unique_ptr<PSO_Context::ToolLender>> tools;
};

