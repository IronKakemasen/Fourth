#include "PreCompileHeader.h"
#include "CreateDepthStencilDesc.h"


CD3DX12_DEPTH_STENCIL_DESC CreateDepthStencilDesc::Create(const PipelineStateDesc::DepthStencilDesc& desc_)
{
	CD3DX12_DEPTH_STENCIL_DESC depthStencilDesc{};
	
	D3D12_DEPTH_WRITE_MASK depthWriteMask{};
	switch (desc_.blendMode)
	{

	case RenderStateComponent::BlendMode::kOpaque:

		depthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;

		break;

	default:

		depthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;

		break;
	}

	depthStencilDesc.DepthEnable = BOOL(desc_.depthWrite);
	depthStencilDesc.DepthFunc = (D3D12_COMPARISON_FUNC)desc_.depthTest;
	depthStencilDesc.DepthWriteMask = depthWriteMask;

	return depthStencilDesc;

}
