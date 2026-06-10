#include "PreCompileHedder.h"
#include "SRV_UAV_Creator.h"


SRV_UAV_Creator::SRV_UAV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
	:ViewCreatorBehavior<D3D12_SHADER_RESOURCE_VIEW_DESC>(createKey_, descriptorHeapClass_)
{

}


void SRV_UAV_Creator::CreateView(GPUBufferBehavior& buffer_)
{
	
}

D3D12_SHADER_RESOURCE_VIEW_DESC SRV_UAV_Creator::CreateViewDesc()
{
	return D3D12_SHADER_RESOURCE_VIEW_DESC{};
}