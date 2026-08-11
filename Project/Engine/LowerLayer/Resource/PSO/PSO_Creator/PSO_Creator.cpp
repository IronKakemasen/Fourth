#include "PreCompileHeader.h"
#include "PSO_Creator.h"
#include "PSO_Assembler/PSO_Assembler.h"
#include "../PSO_Container/PSO_Container.h"



PSO_Context::PSO_Creator::PSO_Creator
(
	NexusFieldProof proof_, 
	std::unique_ptr<Assembler>&& assembler_, 
	PSO_Container* container_
) :assembler(std::move(assembler_)), container(container_)
{

}

template<>
ID3D12PipelineState* PSO_Context::PSO_Creator::Create
(
	PipelineStateDesc::Graphics& srcDesc_,
	ID3D12RootSignature* rootSignature_,
	std::string debugName_
)
{
	return container->Import
	(
		PSO_Container::Local_ImportLicence{},
		assembler->Assemble(Assembler::Local_AssembleLicence{}, srcDesc_, rootSignature_, debugName_)
	);
}
