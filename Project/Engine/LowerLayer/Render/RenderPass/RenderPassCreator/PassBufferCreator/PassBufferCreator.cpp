#include "PreCompileHeader.h"
#include "PassBufferCreator.h"
#include "../../PassDesc/PassRequiredInfo.h"


//外部
#include "../../../../Resource/Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../Resource/Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../../Resource/Buffer/BufferDefinition/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../../../Resource/Buffer/BufferDefinition/BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"

void RenderContext::RenderPassCreator::PassBufferCreator::CreateBuffer
(
	std::string const passName_,
	PassRequiredInfo& info,
	BufferContext::BufferCreator* creator_
)
{
	auto const numColorBufferRequired = info.colorBuffersInfo.size();

	std::vector<ColorBufferDescription> colorBufferDescs;
	for (size_t i = 0;i < numColorBufferRequired;++i)
	{
		auto& tmp = info.colorBuffersInfo[i];
		ColorBufferDescription colorBufferDesc(tmp.clearColor, tmp.width, tmp.height, tmp.format, tmp.numBuffer);
		
		tmp.bufferID = creator_->CreateWithBuffer(colorBufferDesc, passName_ + "[" + std::to_string(i) + "]").first;
	}

	if (info.depthStencilBufferInfo.has_value())
	{
		auto& tmp = info.depthStencilBufferInfo;

		DepthStencilBufferDescription desc
		(
			tmp->width,
			tmp->height,
			tmp->clearDepth,
			tmp->dsvFormat,
			tmp->srvFormat,
			tmp->numBuffer
		);

		tmp->bufferID = creator_->CreateWithBuffer(desc, passName_).first;
	}

}
