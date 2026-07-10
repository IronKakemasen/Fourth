
#include "RenderTargetBufferInfoExtractor.h"

#include "../../../BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../BufferDefinition/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"


BufferContext::RenderTargetBufferInfoExtractor::RenderTargetBufferInfoExtractor()
{
	tmpBufferContainer.reserve(kBufferContainerSize);
}

void BufferContext::RenderTargetBufferInfoExtractor::SwapApplicableBuffer()
{
	for (auto itr = tmpBufferContainer.begin();itr != tmpBufferContainer.end();++itr)
	{
		if ((*itr) == nullptr) continue;

		auto* rtBuffer = dynamic_cast<IRenderTargetBuffer*>(*itr);
		//全てスワップ。シングルバッファは影響なし
		rtBuffer->Swap();
	}

	tmpBufferContainer.clear();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
RequiredRenderingInfo::ColorBuffer BufferContext::RenderTargetBufferInfoExtractor::Exstract(ColorBuffer* buffer_)
{
	RequiredRenderingInfo::ColorBuffer info;

	info.cpuHandle = buffer_->OutProperRTVHeapHandle();
	info.barrier = buffer_->CreateBarrier(Usage::kWrite);

	return info;
}

template<>
RequiredRenderingInfo::Texture BufferContext::RenderTargetBufferInfoExtractor::Exstract(ColorBuffer* buffer_)
{
	RequiredRenderingInfo::Texture info;

	info.srvHeapIndex = buffer_->OutProperSRVHeapIndex();
	info.barrier = buffer_->CreateBarrier(Usage::kRead);

	return info;
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
RequiredRenderingInfo::DepthBuffer BufferContext::RenderTargetBufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_)
{
	RequiredRenderingInfo::DepthBuffer info;
	info.dsvCpuHandle = buffer_->OutProperDSVHeapHandle();
	info.barrier = buffer_->CreateBarrier(Usage::kWrite);

	return info;

}

template<>
RequiredRenderingInfo::Texture BufferContext::RenderTargetBufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_)
{
	RequiredRenderingInfo::Texture info;

	info.srvHeapIndex = buffer_->OutProperSRVHeapIndex();
	info.barrier = buffer_->CreateBarrier(Usage::kRead);

	return info;
}


