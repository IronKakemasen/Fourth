#include "PreCompileHeader.h"
#include "CreateRasterizerDesc.h"


CD3DX12_RASTERIZER_DESC CreateRasterizerDesc::Create(const PipelineStateDesc::RasterizerDesc& desc_)
{
	CD3DX12_RASTERIZER_DESC rasterizerDesc{};

	//カルモード
	rasterizerDesc.CullMode = D3D12_CULL_MODE(desc_.cullMode);
	//三角形の中身を塗りつぶすかどうか
	rasterizerDesc.FillMode = D3D12_FILL_MODE(desc_.fillMode);

	rasterizerDesc.FrontCounterClockwise = FALSE;

	rasterizerDesc.DepthBias = desc_.depthBias;
	rasterizerDesc.DepthBiasClamp = desc_.depthBiasClamp;
	rasterizerDesc.SlopeScaledDepthBias = desc_.slopeScaledDepthBias;

	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.AntialiasedLineEnable = FALSE;
	rasterizerDesc.ForcedSampleCount = 0;
	rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return rasterizerDesc;

}
