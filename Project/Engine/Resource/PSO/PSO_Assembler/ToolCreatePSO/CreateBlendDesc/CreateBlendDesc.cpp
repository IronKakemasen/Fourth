#include "PreCompileHeader.h"
#include "CreateBlendDesc.h"


CD3DX12_BLEND_DESC CreateBlendDesc::Create(const PipelineStateDesc::RenderTargetDesc& srcDesc_)
{
	CD3DX12_BLEND_DESC blendDesc;

	blendDesc.IndependentBlendEnable = TRUE;
	blendDesc.AlphaToCoverageEnable = FALSE;

	for (size_t i = 0;i < srcDesc_.blendModeContainer.size();++i)
	{
		//共通設定
		SetCommonDetails(&blendDesc.RenderTarget[i]);
		//ブレンドモードごとの設定
		SetBranchedDetails(&blendDesc.RenderTarget[i], srcDesc_.blendModeContainer[i]);
	}

	return blendDesc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateBlendDesc::SetCommonDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_)
{
	desc_->RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	desc_->LogicOp = D3D12_LOGIC_OP_NOOP;
	desc_->SrcBlendAlpha = D3D12_BLEND_ONE;
	desc_->BlendOpAlpha = D3D12_BLEND_OP_ADD;
	desc_->DestBlendAlpha = D3D12_BLEND_ZERO;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateBlendDesc::SetBranchedDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_, RenderStateComponent::BlendMode blendMode_)
{
	switch (blendMode_)
	{
	case RenderStateComponent::BlendMode::kOpaque:

		desc_->BlendEnable = FALSE;
		desc_->SrcBlend = D3D12_BLEND_ONE;
		desc_->BlendOp = D3D12_BLEND_OP_ADD;
		desc_->DestBlend = D3D12_BLEND_ZERO;

		break;

	case RenderStateComponent::BlendMode::kAdditive:

		desc_->BlendEnable = TRUE;
		desc_->SrcBlend = D3D12_BLEND_SRC_ALPHA;
		desc_->BlendOp = D3D12_BLEND_OP_ADD;
		desc_->DestBlend = D3D12_BLEND_ONE;

		break;

	case RenderStateComponent::BlendMode::kAlphaBlend:

		desc_->BlendEnable = TRUE;
		desc_->SrcBlend = D3D12_BLEND_SRC_ALPHA;
		desc_->BlendOp = D3D12_BLEND_OP_ADD;
		desc_->DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

		break;

	}

}
