#pragma once
#include "../RootSignatureContext.h"
#include "../RootSignatureCmds.h"

class RootSignatureContext::RootSignatureCreator
{
public:

	RootSignatureCreator
	(
		NexusFieldProof proof_,
		std::unique_ptr<Assembler>&& assembler_,
		RootSignatureLibrary* library_
	);

	RootSignatureCmds::CreateGraphicsRootSigCmd CreateGraphicsrootSigCmd(CmdProviderKey key_);

private:

	//作成関数
	template<typename DescType>
	ID3D12RootSignature* Create(const DescType& desc_);

	std::unique_ptr<Assembler> assembler;
	RootSignatureLibrary* library;
};


template<>
ID3D12RootSignature* RootSignatureContext::RootSignatureCreator::Create(const RootSignatureDesc::Graphics& desc_);




