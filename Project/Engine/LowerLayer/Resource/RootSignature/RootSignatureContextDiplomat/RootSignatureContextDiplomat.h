#pragma once
#include "../RootSignatureContext.h"

class RootSignatureContextDiplomat
{
public:

	RootSignatureContextDiplomat
	(
		RootSignatureContext::NexusFieldProof proof,
		std::unique_ptr<RootSignatureContext::ToolLender>&& toolLender_
	);


private:

	std::tuple
	<
		std::unique_ptr<RootSignatureContext::ToolLender>
	>tools;

};

