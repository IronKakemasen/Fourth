#pragma once
#include "../../../PipelineStateDesc.h"


//DepthStencilDescを生成
struct CreateDepthStencilDesc
{
	CD3DX12_DEPTH_STENCIL_DESC Create(const std::optional<PipelineStateComponent::DepthStencilDesc> srcDesc_);

private:
	void SetBranchedDetails(CD3DX12_DEPTH_STENCIL_DESC* desc_, const PipelineStateComponent::DepthStencilDesc& srcDesc_);
	void SetDetailsDirectly(CD3DX12_DEPTH_STENCIL_DESC* desc_, const PipelineStateComponent::DepthStencilDesc& srcDesc_);
};

