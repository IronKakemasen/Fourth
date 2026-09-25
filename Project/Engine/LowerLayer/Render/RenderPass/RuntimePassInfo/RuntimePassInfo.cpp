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
			info.viewport = AssembleMatrix<D3D12_VIEWPORT>(src.width, src.height);
			info.scissorRect = AssembleMatrix<D3D12_RECT>(src.width, src.height);
		}
	}

	//深度ステンシルバッファ
	{
		auto& info = depthStencilBufferInfo;
		auto const& src = desc_.depthStencilBufferInfo;

		if (src.has_value())
		{
			depthStencilBufferInfo.emplace();

			info->bufferID			= src->bufferID;
			info->clearDepth		= src->clearDepth;
			info->clearStencil		= src->clearStencil;
			info->doesClearStencil  = src->doesClearStencil;
		}
	}

}


template<>
D3D12_VIEWPORT RenderContext::RuntimePassInfo::AssembleMatrix(uint32_t width_, uint32_t height_)
{
	D3D12_VIEWPORT viewport;

	viewport.Width = static_cast<FLOAT>(width_);
	viewport.Height = static_cast<FLOAT>(height_);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	return viewport;
}

template<>
D3D12_RECT RenderContext::RuntimePassInfo::AssembleMatrix(uint32_t width_, uint32_t height_)
{
	D3D12_RECT scissorRect;

	scissorRect.right = static_cast<LONG>(width_);
	scissorRect.bottom = static_cast<LONG>(height_);
	scissorRect.left = static_cast<LONG>(0.0f);
	scissorRect.top = static_cast<LONG>(0.0f);

	return scissorRect;
}
