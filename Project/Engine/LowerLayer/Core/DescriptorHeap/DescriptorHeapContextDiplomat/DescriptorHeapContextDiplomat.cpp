#include "PreCompileHeader.h"
#include "DescriptorHeapContextDiplomat.h"
#include "DescriptorHeapToolLender/DescriptorHeapToolLender.h"


DescriptorHeapContextDiplomat::DescriptorHeapContextDiplomat
(
	DescriptorHeapContext::InstanceKey key_,
	std::unique_ptr<DescriptorHeapContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<DescriptorHeapContext::ToolLender>>(tools) = std::move(toolLender_);
}
