#pragma once

class Nexus;
class DeviceContextDiplomat;

class PSO_Context
{
protected:

	using CommandCreateGraphicsPSO = std::function<void(ID3D12PipelineState** doublePtr_pso_, D3D12_PIPELINE_STATE_STREAM_DESC* streamDesc_)>;
	using CommandCreateComputePSO = std::function<void(ID3D12PipelineState** doublePtr_pso_, D3D12_COMPUTE_PIPELINE_STATE_DESC* computeDesc_)>;

public:

	//PSOを構築するもの
	class Assembler;

	//自身のインスタンスキー
	struct InstanceKey;

	PSO_Context
	(
		InstanceKey key_,
		DeviceContextDiplomat* deviceContextDiplomat_
	);

	~PSO_Context();


private:

	std::unique_ptr<Assembler> assembler;


	//ただのpsoのコンテナ
	std::vector<Microsoft::WRL::ComPtr<ID3D12PipelineState>> psoContainer;
};


struct PSO_Context::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
