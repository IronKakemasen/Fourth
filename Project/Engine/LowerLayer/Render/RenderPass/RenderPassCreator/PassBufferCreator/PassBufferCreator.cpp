#include "PreCompileHeader.h"
#include "PassBufferCreator.h"


//外部
#include "../../../../Resource/Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../Resource/Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../../Resource/Buffer/BufferDefinition/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../../../Resource/Buffer/BufferDefinition/BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"

void RenderContext::RenderPassCreator::PassBufferCreator::CreateBuffer
(
	std::string const passName_,
	PassDesc& desc_,
	BufferContext::BufferCreator* creator_
)
{
	auto const& colorBuffersInfo = desc_.WatchColorBuffersInfo();
	auto const numColorBufferRequired = colorBuffersInfo.size();

	std::vector<ColorBufferDescription> colorBufferDescs;
	for (size_t i = 0;i < numColorBufferRequired;++i)
	{
		auto const& tmp = colorBuffersInfo[i];
		ColorBufferDescription colorBufferDesc(tmp.clearColor, tmp.width, tmp.height, tmp.format, tmp.numBuffer);
		
		desc_.SetColorBufferUniqueID(creator_->CreateWithBuffer(colorBufferDesc, passName_ + "[" + std::to_string(i) + "]").first, i);
	}

	if (desc_.DoesDepthStencilBufferInfoContains())
	{
		auto const& tmp = desc_.WatchDepthStencilBufferInfo();

		DepthStencilBufferDescription desc
		(
			tmp->width,
			tmp->height,
			tmp->clearDepth,
			tmp->clearStencil,
			tmp->dsvFormat,
			tmp->srvFormat,
			tmp->numBuffer
		);

		desc_.SetDepthStencilBufferUniqueID(creator_->CreateWithBuffer(desc, passName_).first);
	}

}
