#pragma once
#include "../PSO_Context.h"
#include "PipelineStateDesc.h"

class PSO_Context::PSO_Creator
{
public:

	PSO_Creator(NexusFieldProof proof_, std::unique_ptr<Assembler>&& assembler_, PSO_Container* container_);
	
	template<typename DescType>
	ID3D12PipelineState* Create
	(
		DescType& srcDesc_,
		ID3D12RootSignature* rootSignature_,
		std::string debugName_
	);

private:

	std::unique_ptr<Assembler>&& assembler;
	PSO_Container* container;
};

template<>
ID3D12PipelineState* PSO_Context::PSO_Creator::Create
(
	PipelineStateDesc::Graphics& srcDesc_,
	ID3D12RootSignature* rootSignature_,
	std::string debugName_
);
