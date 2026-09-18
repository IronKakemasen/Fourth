#include "PreCompileHeader.h"
#include "PassBufferCreator.h"


//外部
#include "../../../../Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../../Buffer/BufferDefinition/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../../../Buffer/BufferDefinition/BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"

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
				
		desc_.SetColorBufferUniqueID(creator_->CreateWithBuffer(colorBufferDesc, passName_).first, i);
	}

	if (desc_.WatchDepthStencilBufferInfo().has_value())
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
