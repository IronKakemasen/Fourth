#pragma once
#include "../../RootSignatureContext.h"
#include "RootSignatureCmds.h"

class RootSignatureContext::CmdProvider
{
	template<typename CmdType>
	struct LicenceTypeTraits;

	struct UsesCreateGraphicsRootSigCmdLicence;

public:

	template<typename CmdType>
	using LicenceType = typename LicenceTypeTraits<CmdType>::Type;

	CmdProvider(NexusFieldProof proof_, RootSignatureCreator* creator_);

	///コマンド提供
	template<typename CmdType>
	CmdType Provide(typename LicenceTypeTraits<CmdType>::Type type_);


private:

	RootSignatureCreator* creator;
};


template<>
struct RootSignatureContext::CmdProvider::LicenceTypeTraits<RootSignatureCmds::CreateGraphicsRootSigCmd>
{
	using Type = UsesCreateGraphicsRootSigCmdLicence;
};


template<>
RootSignatureCmds::CreateGraphicsRootSigCmd RootSignatureContext::CmdProvider::Provide<RootSignatureCmds::CreateGraphicsRootSigCmd>
(typename LicenceTypeTraits<RootSignatureCmds::CreateGraphicsRootSigCmd>::Type type_);
