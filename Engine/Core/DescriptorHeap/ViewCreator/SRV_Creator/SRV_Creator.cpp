#include "PreCompileHedder.h"
#include "SRV_Creator.h"


SRV_Creator::SRV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
	:ViewCreatorBehavior(createKey_, descriptorHeapClass_)
{

}


[[nodiscard]] uint32_t SRV_Creator::CreateView(const GPUBufferBehavior& buffer_)
{
	return 1;
}
