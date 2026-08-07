#include "PreCompileHeader.h"
#include "RootSignatureContextDiplomat.h"
#include "RootSignatureToolLender/RootSignatureToolLender.h"
#include "RootSignatureCmdProvider/RootSignatureCmdProvider.h"


RootSignatureContextDiplomat::RootSignatureContextDiplomat
(
	RootSignatureContext::NexusFieldProof proof,
	std::unique_ptr<RootSignatureContext::ToolLender>&& toolLender_,
	std::unique_ptr<RootSignatureContext::CmdProvider>&& cmdProvider_

)
{
	std::get<std::unique_ptr<RootSignatureContext::ToolLender>>(tools) = std::move(toolLender_);
	std::get<std::unique_ptr<RootSignatureContext::CmdProvider>>(tools) = std::move(cmdProvider_);

}
