#include "PreCompileHeader.h"
#include "RuntimePassInfo.h"
#include "../PassDesc/PassDesc.h"

RenderContext::RuntimePassInfo::RuntimePassInfo
(
	NexusFieldProof proof_,
	std::unique_ptr<PassDesc> desc_,
	std::unordered_map<std::string, BufferUniqueID> const& idMap_,
	UINT const refOffset_
)
{
	///パスディスクからランタイムに必要な情報のみピック
	//ここでPassDescのお役は終了
	PickUpRuntimeRequirementsFromDesc(*desc_);

	//その他情報を入力
	InputOtherParams(idMap_, refOffset_);

}

void RenderContext::RuntimePassInfo::InputOtherParams
(
	std::unordered_map<std::string, BufferUniqueID> const& idMap_,
	UINT const refOffset_
)
{
	referenceBufferIDMap = idMap_;
	rootConstants.offset = refOffset_;
	rootConstants.numTextureUse = UINT(idMap_.size());
}

void RenderContext::RuntimePassInfo::PickUpRuntimeRequirementsFromDesc(PassDesc const& desc_)
{

//カラーバッファ
	{
		auto const numColorBuffers = desc_.colorBuffersInfo.size();
		colorBuffersInfo.resize(numColorBuffers);

		for (size_t i = 0;i < numColorBuffers;++i)
		{
			auto& info = colorBuffersInfo[i];
			auto const& src = desc_.colorBuffersInfo[i];

			info.blendMode = src.blendMode;
			info.bufferID = src.bufferID;
			info.clearColor = src.clearColor;
			info.height = src.height;
			info.width = src.width;
		}
	}

	//深度ステンシルバッファ
	{
		auto& info = depthStencilBufferInfo;
		auto const& src = desc_.depthStencilBufferInfo;

		if (src.has_value())
		{
			depthStencilBufferInfo.emplace();

			info->bufferID		= src->bufferID;
			info->clearDepth	= src->clearDepth;
			info->clearStencil	= src->clearStencil;
		}
	}

}
