#include "PreCompileHeader.h"
#include "CommandCreatePSO.h"


namespace
{
	auto fileName = "CommandCreatePSO.cpp";
}

CommandCreatePSO::CommandCreatePSO(DeviceContext::GenerateKey generateKey_) :DeviceContextCommandBehavior(generateKey_)
{

}

CommandCreatePSO::~CommandCreatePSO()
{

}


void CommandCreatePSO::CreateComputePipelineState
(
	ID3D12Device8* device_,
	ID3D12PipelineState** doublePtr_pso_,
	D3D12_COMPUTE_PIPELINE_STATE_DESC* computeDesc_
)
{
	HRESULT hr = device_->CreateComputePipelineState(computeDesc_, IID_PPV_ARGS(doublePtr_pso_));
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "Compute用のPSO生成失敗", fileName);
}

void CommandCreatePSO::CreateGraphicsPipelineState
(
	ID3D12Device8* device_,
	ID3D12PipelineState** doublePtr_pso_,
	D3D12_PIPELINE_STATE_STREAM_DESC* streamDesc_
)
{
	HRESULT hr = device_->CreatePipelineState(streamDesc_,IID_PPV_ARGS(doublePtr_pso_));
	ErrorMessageOutput::Assert::DetectError(SUCCEEDED(hr), "Graphics用のPSO生成失敗", fileName);
}
