#include "PreCompileHedder.h"
#include "DSV_Creator.h"



DSV_Creator::DSV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
	:ViewCreatorBehavior<D3D12_DEPTH_STENCIL_VIEW_DESC>(createKey_, descriptorHeapClass_)
{

}


void DSV_Creator::CreateView(GPUBufferBehavior& buffer_)
{
	
}

D3D12_DEPTH_STENCIL_VIEW_DESC DSV_Creator::CreateViewDesc()
{
	return D3D12_DEPTH_STENCIL_VIEW_DESC{};
}
