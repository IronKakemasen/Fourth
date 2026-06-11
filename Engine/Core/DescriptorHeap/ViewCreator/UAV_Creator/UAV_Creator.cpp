#include "PreCompileHedder.h"
#include "UAV_Creator.h"

UAV_Creator::UAV_Creator(DescriptorHeapContext::CreateKey createKey_, DescriptorHeapClass* descriptorHeapClass_)
	:ViewCreatorBehavior<D3D12_UNORDERED_ACCESS_VIEW_DESC>(createKey_, descriptorHeapClass_)
{

}


void UAV_Creator::CreateView(GPUBufferBehavior& buffer_, uint32_t allocateIndex_)
{

}

D3D12_UNORDERED_ACCESS_VIEW_DESC UAV_Creator::CreateViewDesc()
{
	return D3D12_UNORDERED_ACCESS_VIEW_DESC{};
}
