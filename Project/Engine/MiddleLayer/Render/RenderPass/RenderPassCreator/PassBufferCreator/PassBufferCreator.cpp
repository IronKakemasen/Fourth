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

namespace
{
	auto const fileName = "PassBufferCreator.cpp";

}

void RenderContext::RenderPassCreator::PassBufferCreator::CreateBuffer
(
	std::string const passName_,
	PassDesc& desc_,
	std::unordered_map<std::string, BufferUniqueID>& passBufferCache_,
	std::unordered_map<std::string, RequiredBufferInfo::ColorBuffer*>& colorBufferInfosMapCache_,
	std::unordered_map<std::string, RequiredBufferInfo::DepthStencilBuffer*>& depthBufferInfoMapCache_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	BufferContext::ToolLender::LicenceType<BufferContext::BufferCreator> borrowLicence;
	auto bufferCreator = bufferContextDiplomat_.Access<BufferContext::ToolLender>()->Lend<BufferContext::BufferCreator>(borrowLicence);


	//カラーバッファを作成
	auto& colorBuffersInfo = desc_.colorBuffersInfo;
	auto const numColorBufferRequired = colorBuffersInfo.size();
	for (size_t i = 0;i < numColorBufferRequired;++i)
	{
		auto& info = colorBuffersInfo[i];

#ifdef _DEBUG

		//バッファ名の重複チェック
		ErrorMessageOutput::Assert::DetectError
		(
			passBufferCache_.find(info.bufferName) == passBufferCache_.end(),
			passName_ + " のカラーバッファ名: " + info.bufferName + "が被ってる",
			fileName
		);

#endif // _DEBUG

		ColorBufferDescription colorBufferDesc(info.clearColor, info.width, info.height, info.format, info.numBuffer);
		
		//バッファを作成し、そのユニークを保存
		BufferUniqueID id = bufferCreator->CreateWithBuffer(colorBufferDesc, info.bufferName).first;

		info.bufferID = id;

		//後にPass達が他Passのバッファを参照するタメに必要なのでこちらにも保存
		passBufferCache_[info.bufferName] = id;

		//後に書き込みシェアバッファ検索用として追加
		colorBufferInfosMapCache_[info.bufferName] = &colorBuffersInfo[i];
	}

	//深度ステンシルバッファを作成
	if (desc_.depthStencilBufferInfo.has_value())
	{
		auto& info = desc_.depthStencilBufferInfo;

#ifdef _DEBUG

		//バッファ名の重複チェック
		ErrorMessageOutput::Assert::DetectError
		(
			passBufferCache_.find(info->bufferName) == passBufferCache_.end(),
			passName_ + " の深度バッファ名: " + info->bufferName + "が被ってる",
			fileName
		);

		//書き込みシェアバッファと自前バッファが同時に存在しているのは間違っているので
		ErrorMessageOutput::Assert::DetectError
		(
			desc_.writeSharingDepthBufferName.size() == 0,
			passName_ + ": 書き込みシェアバッファと自前バッファが同時に存在している",
			fileName
		);

#endif // _DEBUG

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

		desc_.depthStencilBufferInfo->bufferID = id;

		//後にPass達が他Passのバッファを参照するタメに必要なのでこちらにも保存
		passBufferCache_[info->bufferName] = id;

		//後に書き込みシェアバッファ検索用として追加
		depthBufferInfoMapCache_[info->bufferName] = &desc_.depthStencilBufferInfo.value();
	}


#ifdef _DEBUG

	//書き込み先バッファが最低でも１つあるかチェック

	size_t writeInBufferCnt =
		(size_t)numColorBufferRequired +
		desc_.writeSharingColorBufferNames.size() +
		(size_t)desc_.depthStencilBufferInfo.has_value() +
		desc_.writeSharingDepthBufferName.size();

	ErrorMessageOutput::Assert::DetectError
	(
		writeInBufferCnt > 0,
		passName_ + ": 書き込み先バッファが１つもないやん",
		fileName
	);

#endif
}
