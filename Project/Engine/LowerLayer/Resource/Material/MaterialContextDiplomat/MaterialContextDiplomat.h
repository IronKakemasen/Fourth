#pragma once
#include "../MaterialContext.h"

class MaterialContextDiplomat
{
public:

	MaterialContextDiplomat
	(
		MaterialContext::NexusFieldProof proof_,
		std::unique_ptr<MaterialContext::ExecutionAgent>&& executionAgent_,
		std::unique_ptr<MaterialContext::ToolLender>&& toolLender_
	);

	~MaterialContextDiplomat();

	template<typename ToolType>
	auto& Access()
	{
		return *std::get<std::unique_ptr<ToolType>>(tools);
	}

private:

	std::tuple
	<
		std::unique_ptr<MaterialContext::ExecutionAgent>,
		std::unique_ptr<MaterialContext::ToolLender>
	>tools;

};

