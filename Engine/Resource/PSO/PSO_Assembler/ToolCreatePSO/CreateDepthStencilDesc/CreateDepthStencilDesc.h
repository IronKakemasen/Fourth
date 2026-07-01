#pragma once
#include "../../PipelineStateDesc.h"


//DepthStencilDescを生成
struct CreateDepthStencilDesc
{
	CD3DX12_DEPTH_STENCIL_DESC Create(const PipelineStateDesc::DepthStencilDesc& desc_);

};

