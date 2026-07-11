
#include "RenderPassMaterialProvider.h"


SwapChainContext::RenderPassMaterialProvider::RenderPassMaterialProvider(SwapChainContext::ColorBuffer* colorBuffer_)
	:colorBuffer(colorBuffer_)
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] SwapChainContext::RenderPassMaterialProvider::Materials SwapChainContext::RenderPassMaterialProvider::ProvideForBegine(UINT frameIndex_)
{
	
	SwapChainContext::RenderPassMaterialProvider::Materials::ColorBuffer materialC;

	//カラーバッファの提供材料
	{
		materialC.scissorRect = &colorBuffer->scissorRect;
		materialC.viewport = &colorBuffer->viewport;

		auto& dstBuffer = colorBuffer->buffers.at(frameIndex_);
		//ハンドル
		materialC.handle = dstBuffer.cpuHandle;
		//クリアカラー
		materialC.clearColor = colorBuffer->desc->clearColor;

		//今後もリソースステートの遷移は固定だと思うので決め打ち
		D3D12_RESOURCE_STATES after = D3D12_RESOURCE_STATE_RENDER_TARGET;
		materialC.barrier = dstBuffer.CreateBarrier(after);
	}

	return SwapChainContext::RenderPassMaterialProvider::Materials
	(
		materialC
	);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] D3D12_RESOURCE_BARRIER SwapChainContext::RenderPassMaterialProvider::ProvideEnd(UINT frameIndex_)
{
	auto& dstBuffer = colorBuffer->buffers.at(frameIndex_);

	//今後もリソースステートの遷移は固定だと思うので決め打ち
	D3D12_RESOURCE_STATES after = D3D12_RESOURCE_STATE_PRESENT;
	
	return dstBuffer.CreateBarrier(after);
}
