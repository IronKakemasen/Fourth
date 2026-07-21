#include "PreCompileHeader.h"
#include "StaticStructuredBuffer.h"


StaticStructuredBuffer::StaticStructuredBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
	const BufferDescriptionBehavior& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resourceContainer_), description_)
{

}



SRVHeapIndex StaticStructuredBuffer::OutProperSRVHeapIndex(int frameIndex_)const
{
	return WatchIndex<ViewType::kSRV, SRVHeapIndex >(0);
}


D3D12_RESOURCE_BARRIER StaticStructuredBuffer::CreateBarrierAsReading()
{
	return buffers[0].CreateBarrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE);
}

