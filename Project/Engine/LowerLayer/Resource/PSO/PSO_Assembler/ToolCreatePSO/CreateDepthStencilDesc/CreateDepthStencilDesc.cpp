#include "CreateDepthStencilDesc.h"


CD3DX12_DEPTH_STENCIL_DESC CreateDepthStencilDesc::Create(const std::optional<PipelineStateDesc::DepthStencilDesc> srcDesc_)
{
	CD3DX12_DEPTH_STENCIL_DESC depthStencilDesc{};
	
	if (srcDesc_)
	{
		SetBranchedDetails(&depthStencilDesc, *srcDesc_);
		SetDetailsDirectly(&depthStencilDesc, *srcDesc_);
	}
	//ディプスバッファ使わんのなら
	else
	{
		depthStencilDesc.DepthEnable = FALSE;
	}

	return depthStencilDesc;

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateDepthStencilDesc::SetBranchedDetails(CD3DX12_DEPTH_STENCIL_DESC* desc_, const PipelineStateDesc::DepthStencilDesc& srcDesc_)
{
	D3D12_DEPTH_WRITE_MASK depthWriteMask{};

	switch (srcDesc_.blendMode)
	{

	case RenderStateComponent::BlendMode::kOpaque:

		depthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;

		break;

	//kOpaque以外は全て深度書き込み無効とする
	default:

		depthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;

		break;
	}


	desc_->DepthWriteMask = depthWriteMask;

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateDepthStencilDesc::SetDetailsDirectly(CD3DX12_DEPTH_STENCIL_DESC* desc_, const PipelineStateDesc::DepthStencilDesc& srcDesc_)
{
	desc_->DepthEnable = BOOL(srcDesc_.depthEnable);
	desc_->DepthFunc = RenderPassComponent ::Convert(srcDesc_.depthTest);
}