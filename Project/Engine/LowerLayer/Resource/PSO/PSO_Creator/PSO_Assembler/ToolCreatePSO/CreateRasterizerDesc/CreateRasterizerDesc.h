#pragma once
#include "../../../PipelineStateDesc.h"



//RasterizerDescを生成
struct CreateRasterizerDesc
{
	CD3DX12_RASTERIZER_DESC Create(const PipelineStateComponent::RasterizerDesc& srcDesc_);

private:

	void SetDetailsDirectly(CD3DX12_RASTERIZER_DESC* desc_, const PipelineStateComponent::RasterizerDesc& srcDesc_);
	void SetCommonDetails(CD3DX12_RASTERIZER_DESC* desc_);
};

