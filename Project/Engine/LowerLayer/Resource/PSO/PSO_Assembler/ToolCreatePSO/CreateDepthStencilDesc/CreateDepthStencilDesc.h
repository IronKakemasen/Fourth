#pragma once
#include "../../PipelineStateDesc.h"


//DepthStencilDescを生成
struct CreateDepthStencilDesc
{
	CD3DX12_DEPTH_STENCIL_DESC Create(const std::optional<PipelineStateDesc::DepthStencilDesc> srcDesc_);

private:
	void SetBranchedDetails(CD3DX12_DEPTH_STENCIL_DESC* desc_, const PipelineStateDesc::DepthStencilDesc& srcDesc_);
	void SetDetailsDirectly(CD3DX12_DEPTH_STENCIL_DESC* desc_, const PipelineStateDesc::DepthStencilDesc& srcDesc_);
};

