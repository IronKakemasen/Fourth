#pragma once
#include "../DeviceContextCommandBehavior.h"


//PSO生成コマンド
struct CommandCreatePSO : public DeviceContextCommandBehavior
{
	//DeviceContext::CommandProviderクラスのみ生成可能
	CommandCreatePSO(DeviceContext::GenerateKey generateKey_);

	template<typename DescType>
	void CreatePipelineState
	(
		ID3D12Device8* device_,
		ID3D12PipelineState** doublePtr_pso_,
		DescType* desc_
	);

};

template<>
void CommandCreatePSO::CreatePipelineState
(
	ID3D12Device8* device_,
	ID3D12PipelineState** doublePtr_pso_,
	D3D12_COMPUTE_PIPELINE_STATE_DESC* desc_
);

template<>
void CommandCreatePSO::CreatePipelineState
(
	ID3D12Device8* device_,
	ID3D12PipelineState** doublePtr_pso_,
	D3D12_PIPELINE_STATE_STREAM_DESC* desc_
);
