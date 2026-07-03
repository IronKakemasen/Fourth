#pragma once



class Nexus;
class ShaderContext;

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
		ShaderContext& shaderContext_,
		CommandCreateGraphicsPSO cmdCreateGraphicsPSO_,
		CommandCreateComputePSO cmdCreateComputePSO_
	);

	~PSO_Context();


private:

	std::unique_ptr<Assembler> assembler;

	void InstantiatePSO_Assembler
	(
		InstanceKey key_,
		CommandCreateGraphicsPSO cmdCreateGraphicsPSO_,
		CommandCreateComputePSO cmdCreateComputePSO_
	);
};


struct PSO_Context::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};
