#include "PreCompileHeader.h"
#include "BlendDescCreator.h"


void BlendDescCreator::SetCommonDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_)
{
	desc_->RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	desc_->BlendEnable = TRUE;
	desc_->LogicOp = D3D12_LOGIC_OP_NOOP;
	desc_->SrcBlendAlpha = D3D12_BLEND_ONE;
	desc_->BlendOpAlpha = D3D12_BLEND_OP_ADD;
	desc_->DestBlendAlpha = D3D12_BLEND_ZERO;
}

void BlendDescCreator::SetSpecificDetails(D3D12_RENDER_TARGET_BLEND_DESC* desc_, RenderStateComponent::BlendMode blendMode_)
{
	switch (blendMode_)
	{
		case RenderStateComponent::BlendMode::kNormal:

		desc_->SrcBlend = D3D12_BLEND_SRC_ALPHA;
		desc_->BlendOp = D3D12_BLEND_OP_ADD;
		desc_->DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

		break;

	case RenderStateComponent::BlendMode::kAdd:

		desc_->SrcBlend = D3D12_BLEND_SRC_ALPHA;
		desc_->BlendOp = D3D12_BLEND_OP_ADD;
		desc_->DestBlend = D3D12_BLEND_ONE;

		break;
	}

}
