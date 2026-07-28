
#include "UploadStructuredBuffer.h"


UploadStructuredBuffer::UploadStructuredBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
	const BufferDescriptionBehavior& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resourceContainer_), description_)
{
	Map({ buffers[0].resource.Get(),buffers[1].resource.Get() });

}

UploadStructuredBuffer::~UploadStructuredBuffer()
{
	buffers[0].UnMap();
	buffers[1].UnMap();
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SRVHeapIndex UploadStructuredBuffer::OutProperSRVHeapIndex(int frameIndex_)const
{
	return WatchIndex<ViewType::kSRV, SRVHeapIndex >(frameIndex_);
}
