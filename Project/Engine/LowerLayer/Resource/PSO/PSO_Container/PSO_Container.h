#pragma once
#include "../PSO_Context.h"

class PSO_Context::PSO_Container
{
public:

	struct Local_ImportLicence;

	PSO_Container(NexusFieldProof proof_);

	ID3D12PipelineState* Import(Local_ImportLicence licence_,Microsoft::WRL::ComPtr<ID3D12PipelineState>&& data_);

private:

	//ただのpsoのコンテナ
	std::vector<Microsoft::WRL::ComPtr<ID3D12PipelineState>> psoContainer;

};

struct PSO_Context::PSO_Container::Local_ImportLicence
{
private:

	friend class PSO_Context::PSO_Creator;
	explicit Local_ImportLicence() = default;
};



