#include "PreCompileHeader.h"
#include "PassBufferCreator.h"


//外部
#include "../../../../../LowerLayer/Buffer/BufferCreateTools/BufferCreator.h"
#include "../../../../../LowerLayer/Buffer/BufferDefinition/GPUBuffer/ColorBuffer/ColorBuffer.h"
#include "../../../../../LowerLayer/Buffer/BufferDefinition/BufferDescriptions/ColorBufferDescription/ColorBufferDescription.h"
#include "../../../../../LowerLayer/Buffer/BufferDefinition/BufferDescriptions/DepthStencilBufferDescription/DepthStencilBufferDescription.h"
#include "../../../../../LowerLayer/Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../../../LowerLayer/Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../../../LowerLayer/Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLenderLicence.h"


void RenderContext::RenderPassCreator::PassBufferCreator::CreateBuffer
(
	std::string const passName_,
	PassDesc& desc_,
	std::unordered_map<std::string, BufferUniqueID>& passBufferCache_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> borrowLicence;
	auto bufferCreator = bufferContextDiplomat_.Access<BufferContext::ToolLender>()->Lend<BufferContext::BufferCreator>(borrowLicence);


	auto& colorBuffersInfo = desc_.colorBuffersInfo;
	auto const numColorBufferRequired = colorBuffersInfo.size();

	//カラーバッファを作成
	std::vector<ColorBufferDescription> colorBufferDescs;
	for (size_t i = 0;i < numColorBufferRequired;++i)
	{
		auto& info = colorBuffersInfo[i];
		ColorBufferDescription colorBufferDesc(info.clearColor, info.width, info.height, info.format, info.numBuffer);
		
		//バッファを作成し、そのユニークを保存
		BufferUniqueID id = bufferCreator->CreateWithBuffer(colorBufferDesc, info.bufferName).first;
		//後にPass達が他Passのバッファを参照するタメに必要なのでこちらにも保存
		passBufferCache_[info.bufferName] = id;

		info.bufferID = id;
	}

	//深度ステンシルバッファを作成

	if (desc_.depthStencilBufferInfo.has_value())
	{
		auto& info = desc_.depthStencilBufferInfo;

		DepthStencilBufferDescription desc
		(
			info->width,
			info->height,
			info->clearDepth,
			info->clearStencil,
			info->dsvFormat,
			info->srvFormat,
			info->numBuffer
		);

		//バッファを作成し、そのユニークを保存
		BufferUniqueID id = bufferCreator->CreateWithBuffer(desc, info->bufferName).first;
		//後にPass達が他Passのバッファを参照するタメに必要なのでこちらにも保存
		passBufferCache_[info->bufferName] = id;

		desc_.depthStencilBufferInfo->bufferID = id;
	}

}
