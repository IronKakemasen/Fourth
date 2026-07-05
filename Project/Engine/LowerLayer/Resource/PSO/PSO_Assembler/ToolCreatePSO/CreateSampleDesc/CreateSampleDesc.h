#pragma once
#include "../../PipelineStateDesc.h"


struct CreateSampleDesc
{
	DXGI_SAMPLE_DESC Create(const PipelineStateDesc::SampleDesc& desc_);
};

