
#include "CreateSampleDesc.h"

DXGI_SAMPLE_DESC CreateSampleDesc::Create(const PipelineStateDesc::SampleDesc& desc_)
{
	DXGI_SAMPLE_DESC sampleDesc = {};
	sampleDesc.Count = 1;
	sampleDesc.Quality = 0;

	return sampleDesc;
}