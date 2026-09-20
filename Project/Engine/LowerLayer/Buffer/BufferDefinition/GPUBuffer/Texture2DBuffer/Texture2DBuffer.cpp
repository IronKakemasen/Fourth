#include "PreCompileHeader.h"
#include "Texture2DBuffer.h"

Texture2DBuffer::Texture2DBuffer
(
	const InstanceKey& instanceKey_,
	std::string const& name_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
	const BufferDescriptionBehavior& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resourceContainer_), description_)
{

}

SRVHeapIndex Texture2DBuffer::OutProperSRVHeapIndex(int frameIndex_)const
{
	return WatchIndex<ViewType::kSRV, SRVHeapIndex >(0);
}

D3D12_RESOURCE_BARRIER Texture2DBuffer::CreateBarrierAsReading()
{
	return buffers[0].CreateBarrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE);
}
