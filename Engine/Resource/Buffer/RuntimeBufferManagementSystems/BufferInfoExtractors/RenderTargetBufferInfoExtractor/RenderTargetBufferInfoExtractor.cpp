#include "PreCompileHeader.h"
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

	info.width = buffer_->OutWidthAndHeight().first;
	info.height = buffer_->OutWidthAndHeight().second;
	info.cpuHandle = buffer_->OutProperRTVHeapHandle();
	info.clearColor = buffer_->OutProperClearColor();
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

template<>
RequiredRenderingInfo::Format BufferContext::RenderTargetBufferInfoExtractor::Exstract(ColorBuffer* buffer_)
{
	RequiredRenderingInfo::Format info;

	info.format = buffer_->OutProperRTVFormat();
	return info;
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
RequiredRenderingInfo::DepthBuffer BufferContext::RenderTargetBufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_)
{
	RequiredRenderingInfo::DepthBuffer info;

	info.clearDepth = buffer_->OutProperClearColor().at(0);
	//一旦
	info.clearStencil = 0;
	info.dsvCpuHandle = buffer_->OutProperDSVHeapHandle();
	info.width = buffer_->OutWidthAndHeight().first;
	info.height = buffer_->OutWidthAndHeight().second;
	info.barrier = buffer_->CreateBarrier(Usage::kWrite);

	return info;

}

template<>
RequiredRenderingInfo::Format BufferContext::RenderTargetBufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_)
{
	RequiredRenderingInfo::Format info;

	info.format = buffer_->OutProperDSVFormat();
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


