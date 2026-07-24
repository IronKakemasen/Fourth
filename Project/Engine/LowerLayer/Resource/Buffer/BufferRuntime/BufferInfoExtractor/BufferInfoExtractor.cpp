
#include "BufferInfoExtractor.h"

#include "../../BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../BufferDefinition/GPUBuffer/DepthStencilBuffer/DepthStencilBuffer.h"


BufferContext::BufferInfoExtractor::BufferInfoExtractor()
{
	tmpBufferContainer.reserve(kBufferContainerSize);
}

void BufferContext::BufferInfoExtractor::SwapApplicableBuffer()
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

template<>
RenderPath::Pass::RequiredBufferInfo::Texture BufferContext::BufferInfoExtractor::Exstract(ColorBuffer* buffer_)
{
	RenderPath::Pass::RequiredBufferInfo::Texture info;

	info.barrier = buffer_->CreateBarrier(Usage::kRead);
	info.srvHeapIndex = buffer_->OutProperSRVHeapIndex();

	return info;
}

template<>
RenderPath::Pass::RequiredBufferInfo::RenderTarget BufferContext::BufferInfoExtractor::Exstract(ColorBuffer* buffer_)
{
	RenderPath::Pass::RequiredBufferInfo::RenderTarget info;

	info.barrier = buffer_->CreateBarrier(Usage::kWrite);
	info.cpuHandle = buffer_->OutProperRTVHeapHandle();

	return info;
}


template<>
RenderPath::Pass::RequiredBufferInfo::Texture BufferContext::BufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_)
{
	RenderPath::Pass::RequiredBufferInfo::Texture info;

	info.barrier = buffer_->CreateBarrier(Usage::kRead);
	info.srvHeapIndex = buffer_->OutProperSRVHeapIndex();

	return info;

}

template<>
RenderPath::Pass::RequiredBufferInfo::RenderTarget BufferContext::BufferInfoExtractor::Exstract(DepthStencilBuffer* buffer_)
{
	RenderPath::Pass::RequiredBufferInfo::RenderTarget info;

	info.barrier = buffer_->CreateBarrier(Usage::kWrite);
	info.cpuHandle = buffer_->OutProperDSVHeapHandle();

	return info;
}
