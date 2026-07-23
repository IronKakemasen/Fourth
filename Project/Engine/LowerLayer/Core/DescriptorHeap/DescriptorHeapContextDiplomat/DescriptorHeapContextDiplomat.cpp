#include "PreCompileHeader.h"
#include "DescriptorHeapContextDiplomat.h"
#include "DescriptorHeapToolLender/DescriptorHeapToolLender.h"


DescriptorHeapContextDiplomat::DescriptorHeapContextDiplomat
(
	DescriptorHeapContext::NexusFieldProof proof_,
	std::unique_ptr<DescriptorHeapContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<DescriptorHeapContext::ToolLender>>(tools) = std::move(toolLender_);
}
