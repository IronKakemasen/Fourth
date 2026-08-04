#pragma once
#include "../ShaderContext.h"


class ShaderContextDiplomat
{
public:
	ShaderContextDiplomat
	(
		ShaderContext::NexusFieldProof proof_,
		std::unique_ptr<ShaderContext::ToolLender>&& toolLender_
	);

	template <typename ToolType>
	auto* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}


private:

	std::tuple
	<
		std::unique_ptr<ShaderContext::ToolLender>
	>tools;
};

