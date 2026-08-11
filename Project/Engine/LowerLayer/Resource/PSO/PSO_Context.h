#pragma once

class Nexus;
class DeviceContextDiplomat;

class PSO_Context
{
	//PSOを構築するもの
	class Assembler;
	//PSOのユニークを所持するだけ
	class PSO_Container;

protected:

	using CommandCreateGraphicsPSO = std::function<void(ID3D12PipelineState** doublePtr_pso_, D3D12_PIPELINE_STATE_STREAM_DESC* streamDesc_)>;
	using CommandCreateComputePSO = std::function<void(ID3D12PipelineState** doublePtr_pso_, D3D12_COMPUTE_PIPELINE_STATE_DESC* computeDesc_)>;

public:

	class PSO_Creator;

	//自身のインスタンスキー
	struct NexusFieldProof;

	PSO_Context
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat* deviceContextDiplomat_
	);

	~PSO_Context();


private:

	std::unique_ptr<PSO_Creator> psoCreator;
	std::unique_ptr<PSO_Container> psoContainer;

};


struct PSO_Context::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};
