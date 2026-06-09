#include "PreCompileHedder.h"
#include "RTV_Creator.h"

RTV_Creator::RTV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* RTV_descriptorHandleCPUContainer_)
	:ViewCreatorBehavior(createKey_, descriptorHeapClass_), RTV_descriptorHandleCPUContainer(RTV_descriptorHandleCPUContainer_)
{

}

[[nodiscard]] uint32_t RTV_Creator::CreateView(const GPUBufferBehavior& buffer_)
{
	return 1;
}
