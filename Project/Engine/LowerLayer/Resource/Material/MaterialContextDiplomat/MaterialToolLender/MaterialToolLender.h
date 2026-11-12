#pragma once
#include "../../MaterialContext.h"

class MaterialContext::ToolLender
{
public:

	ToolLender
	(
		NexusFieldProof proof_,
		MaterialAttacher* materialAttacher_
	);

	template<typename ToolType>
	auto& Lend()
	{
		return *std::get<ToolType*>(tools);
	}

private:

	std::tuple
	<
		MaterialAttacher*
	>tools;

};

