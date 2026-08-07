#pragma once
#include "../RootSignatureContext.h"

class RootSignatureContextDiplomat
{
public:

	RootSignatureContextDiplomat
	(
		RootSignatureContext::NexusFieldProof proof,
		std::unique_ptr<RootSignatureContext::ToolLender>&& toolLender_,
		std::unique_ptr<RootSignatureContext::CmdProvider>&& cmdProvider_

	);


private:

	std::tuple
	<
		std::unique_ptr<RootSignatureContext::ToolLender>,
		std::unique_ptr<RootSignatureContext::CmdProvider>
	>tools;

};

