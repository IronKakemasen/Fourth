#pragma once
#include "../../RootSignatureContext.h"
#include "../../RootSignatureCmds.h"

class RootSignatureContext::CmdProvider
{
	template<typename CmdType>
	struct CmdTypeTraits;

	struct UsesCreateGraphicsRootSigCmdLicence;

public:

	template<typename CmdType>
	using LicenceType = typename CmdTypeTraits<CmdType>::Type;

	CmdProvider(NexusFieldProof proof_, RootSignatureCreator* creator_);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename CmdTypeTraits<CmdType>::Type licence_);


private:

	RootSignatureCreator* creator;
};


template<>
struct RootSignatureContext::CmdProvider::CmdTypeTraits<RootSignatureCmds::CreateGraphicsRootSigCmd>
{
	using Type = UsesCreateGraphicsRootSigCmdLicence;
};


template<>
RootSignatureCmds::CreateGraphicsRootSigCmd RootSignatureContext::CmdProvider::Provide<RootSignatureCmds::CreateGraphicsRootSigCmd>
(typename CmdTypeTraits<RootSignatureCmds::CreateGraphicsRootSigCmd>::Type licence_);
