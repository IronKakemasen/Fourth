#include "PreCompileHeader.h"
#include "StaticStructuredBuffer.h"
#include "../../BufferDescriptions/StaticStructuredBufferDescription/StaticStructuredBufferDescription.h"


StaticStructuredBuffer::StaticStructuredBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resourceContainer_), std::move(description_))
{

}



SRVHeapIndex StaticStructuredBuffer::OutProperSRVHeapIndex(int frameIndex_)const
{
	return WatchIndex<ViewType::kSRV, SRVHeapIndex >(0);
}
