#pragma once
#include "../../PipelineStateDesc.h"



//RasterizerDescを生成
struct CreateRasterizerDesc
{
	CD3DX12_RASTERIZER_DESC Create(const PipelineStateDesc::RasterizerDesc& desc_);
};

