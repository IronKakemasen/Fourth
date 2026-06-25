#include "PreCompileHeader.h"
#include "ComputeBuffer.h"
#include "../../BufferDescriptions/ComputeBufferDescription/ComputeBufferDescription.h"


ComputeBuffer::ComputeBuffer
(
	const InstanceKey& instanceKey_, 
	std::string name_, 
	Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, 
	Microsoft::WRL::ComPtr<ID3D12Resource> resource2_, 
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resource1_), std::move(resource2_), std::move(description_))
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
ComputeBuffer::CreateNextStepBarriers(ExtractMaterialKey key_)
{
	std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum> barriers;

	if (status == kUAV_SRV)
	{
		// 0 - > SRV , 1 -> UAV
		barriers.at(0) = buffers[0].CreateBarrier(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
		barriers.at(1) = buffers[1].CreateBarrier(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
	}
	else
	{
		barriers.at(0) = buffers[0].CreateBarrier(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
		barriers.at(1) = buffers[1].CreateBarrier(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	}

	return barriers;
}


uint32_t ComputeBuffer::CurrentSRVHeapIndex()
{
	uint32_t heapIndex{};

	if (status == kSRV_UAV)heapIndex = WatchIndex<ViewType::kSRV,uint32_t>(0);
	else heapIndex = WatchIndex<ViewType::kSRV, uint32_t>(1);

	return heapIndex;
}

uint32_t ComputeBuffer::CurrentUAVHeapIndex()
{
	uint32_t heapIndex{};

	if (status == kUAV_SRV)heapIndex = WatchIndex<ViewType::kUAV, uint32_t>(0);
	else heapIndex = WatchIndex<ViewType::kUAV, uint32_t>(1);

	return heapIndex;
}

void ComputeBuffer::Swap()
{
	static Status nextTable[2]
	{
		kUAV_SRV,
		kSRV_UAV
	};

	status = nextTable[status];
}
