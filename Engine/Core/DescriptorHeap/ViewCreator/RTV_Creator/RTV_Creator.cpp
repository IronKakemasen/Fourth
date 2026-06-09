#include "PreCompileHedder.h"
#include "RTV_Creator.h"

RTV_Creator::RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
	:ViewCreatorBehavior(createKey_, descriptorHeapClass_)
{

}

[[nodiscard]] uint32_t RTV_Creator::CreateView(const GPUBufferBehavior& buffer_)
{
	return 1;
}
