#include "PreCompileHedder.h"
#include "DSV_Creator.h"



DSV_Creator::DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_, std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>* DSV_descriptorHandleCPUContainer_)
	:ViewCreatorBehavior<D3D12_DEPTH_STENCIL_VIEW_DESC>(createKey_, descriptorHeapClass_), DSV_descriptorHandleCPUContainer(DSV_descriptorHandleCPUContainer_)
{

}


void DSV_Creator::CreateView(GPUBufferBehavior& buffer_)
{
	
}
