#include "PreCompileHeader.h"
#include "DescriptorHeapToolLender.h"

DescriptorHeapContext::ToolLender::ToolLender(NexusFieldProof proof_, DescriptorHeapContext::ViewCreator* viewCretator_)
{

	std::get<DescriptorHeapContext::ViewCreator*>(tools) = viewCretator_;
}
