#include "PreCompileHeader.h"
#include "RootSignatureContextDiplomat.h"
#include "RootSignatureToolLender/RootSignatureToolLender.h"



RootSignatureContextDiplomat::RootSignatureContextDiplomat
(
	RootSignatureContext::NexusFieldProof proof,
	std::unique_ptr<RootSignatureContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<RootSignatureContext::ToolLender>>(tools) = std::move(toolLender_);
}
