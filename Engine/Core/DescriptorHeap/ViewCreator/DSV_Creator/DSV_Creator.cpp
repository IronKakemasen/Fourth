#include "PreCompileHedder.h"
#include "DSV_Creator.h"



DSV_Creator::DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
	:ViewCreatorBehavior(createKey_, descriptorHeapClass_)
{

}


[[nodiscard]] uint32_t DSV_Creator::CreateView(const GPUBufferBehavior& buffer_)
{
	return 1;
}
