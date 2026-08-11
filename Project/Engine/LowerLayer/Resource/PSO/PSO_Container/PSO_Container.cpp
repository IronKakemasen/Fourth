#include "PreCompileHeader.h"
#include "PSO_Container.h"


PSO_Context::PSO_Container::PSO_Container(NexusFieldProof proof_)
{

}

ID3D12PipelineState* PSO_Context::PSO_Container::Import(Local_ImportLicence licence_,Microsoft::WRL::ComPtr<ID3D12PipelineState>&& data_)
{
	return psoContainer.emplace_back(std::move(data_)).Get();
}
