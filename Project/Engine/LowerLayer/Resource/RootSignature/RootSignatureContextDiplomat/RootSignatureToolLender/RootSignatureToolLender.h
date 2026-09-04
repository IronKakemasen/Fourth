#pragma once
#include "../../RootSignatureContext.h"

class RootSignatureContext::ToolLender
{
	template<typename ToolType>
	struct CmdTypeTraits;

public:

	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_);

	template<typename ToolType>
	auto* Lend(typename CmdTypeTraits<ToolType>::Type type_)
	{
		return std::get<ToolType*>(tools);
	}


private:

	std::tuple<> tools;
};

//template<>
//struct RootSignatureContext::ToolLender::CmdTypeTraits<RootSignatureContext::RootSignatureCreator>
//{
//	using Type = UsesRootSigCreatorLicence;
//};

