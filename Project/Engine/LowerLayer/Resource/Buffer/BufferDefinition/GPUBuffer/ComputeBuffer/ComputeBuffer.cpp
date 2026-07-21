#include "ComputeBuffer.h"


ComputeBuffer::ComputeBuffer
(
	const InstanceKey& instanceKey_,
	std::string name_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
	const BufferDescriptionBehavior& description_
) : GPUBufferBehavior(instanceKey_, name_, std::move(resourceContainer_), description_)
{
	//ステータスを同期
	//SynchronizeStatus(description->numBuffer);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
//ComputeBuffer::CreateNextStepBarriers(ExtractMaterialKey key_)
//{
//	std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum> barriers;
//
//	if (status == kUAV_SRV)
//	{
//		// 0 - > SRV , 1 -> UAV
//		barriers.at(0) = buffers[0].CreateBarrier(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
//		barriers.at(1) = buffers[1].CreateBarrier(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
//	}
//	else
//	{
//		barriers.at(0) = buffers[0].CreateBarrier(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
//		barriers.at(1) = buffers[1].CreateBarrier(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
//	}
//
//	return barriers;
//}


