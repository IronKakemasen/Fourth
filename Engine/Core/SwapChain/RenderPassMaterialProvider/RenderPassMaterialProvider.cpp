#include "PreCompileHeader.h"
#include "RenderPassMaterialProvider.h"
#include "../../../Resource/ResourceBarrier.h"


SwapChainContext::RenderPassMaterialProvider::RenderPassMaterialProvider(SwapChainContext::ColorBuffer* colorBuffer_)
	:colorBuffer(colorBuffer_)
{

}

SwapChainContext::RenderPassMaterialProvider::Materials SwapChainContext::RenderPassMaterialProvider::Provide(UINT frameIndex_)
{
	
	SwapChainContext::RenderPassMaterialProvider::Materials::ColorBuffer materialC;
	SwapChainContext::RenderPassMaterialProvider::Materials::DepthStencilBuffer materialD;


	materialC.scissorRect = &colorBuffer->scissorRect;
	materialC.viewport = &colorBuffer->viewport;

	auto& dstBuffer = colorBuffer->buffers.at(frameIndex_);
	materialC.handle = dstBuffer.cpuHandle;

	materialC.barrier = ResourceBarrier::Create
	(
		dstBuffer.resource.Get(),
		D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		D3D12_RESOURCE_BARRIER_FLAG_NONE,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES
	);

	return SwapChainContext::RenderPassMaterialProvider::Materials
	(
		materialC,
		materialD
	);
}
