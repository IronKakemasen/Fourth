#include "PreCompileHeader.h"
#include "RootSignatureCreator.h"
#include "RootSignatureAssembler/RootSignatureAssembler.h"
#include "../RootSignatureLibrary/RootSignatureLibrary.h"



RootSignatureContext::RootSignatureCreator::RootSignatureCreator
(
	NexusFieldProof proof_,
	std::unique_ptr<Assembler>&& assembler_,
	RootSignatureLibrary* library_
):assembler(std::move(assembler_)), library(library_)
{

}

RootSignatureCmds::CreateGraphicsRootSigCmd RootSignatureContext::RootSignatureCreator::CreateGraphicsrootSigCmd(CmdProviderKey key_)
{
	return [this](const RootSignatureDesc::Graphics& desc_)
	{
		return Create(desc_);
	};
}


template<>
ID3D12RootSignature* RootSignatureContext::RootSignatureCreator::Create(const RootSignatureDesc::Graphics& desc_)
{
	library->Import<Usage::kGraphics>(RootSignatureLibrary::HandleLicence{}, assembler->Assemble(desc_));

	return library->Export<Usage::kGraphics>(RootSignatureLibrary::HandleLicence{});
}
