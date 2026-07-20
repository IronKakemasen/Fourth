#include "PreCompileHeader.h"
#include "DescriptorHeapToolLender.h"

DescriptorHeapContext::ToolLender::ToolLender(InstanceKey key_, DescriptorHeapContext::ViewCreator* viewCretator_) 
{

	std::get<DescriptorHeapContext::ViewCreator*>(tools) = viewCretator_;
}
