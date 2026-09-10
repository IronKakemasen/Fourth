
#include "CommandCreatePSO.h"


namespace
{
	auto fileName = "CommandCreatePSO.cpp";
}

CommandCreatePSO::CommandCreatePSO(DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

template<>
void CommandCreatePSO::CreatePipelineState
(
	ID3D12Device8* device_,
	ID3D12PipelineState** doublePtr_pso_,
	D3D12_COMPUTE_PIPELINE_STATE_DESC* desc_
)
{
	HRESULT hr = device_->CreateComputePipelineState(desc_, IID_PPV_ARGS(doublePtr_pso_));
	ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), "Compute用のPSO生成失敗", fileName);
}

template<>
void CommandCreatePSO::CreatePipelineState
(
	ID3D12Device8* device_,
	ID3D12PipelineState** doublePtr_pso_,
	D3D12_PIPELINE_STATE_STREAM_DESC* desc_
)
{
	HRESULT hr = device_->CreatePipelineState(desc_, IID_PPV_ARGS(doublePtr_pso_));
	ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), "Graphics用のPSO生成失敗", fileName);
}
