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
		
		std::string const bufferName = passName_ + "<" + tmp.bufferName + ">" + "[" + std::to_string(i) + "]";
		
		desc_.SetColorBufferUniqueID(creator_->CreateWithBuffer(colorBufferDesc, bufferName).first, i);
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

		auto const bufferName = passName_ + "<" + tmp->bufferName + ">";

		desc_.SetDepthStencilBufferUniqueID(creator_->CreateWithBuffer(desc, bufferName).first);
	}

}
