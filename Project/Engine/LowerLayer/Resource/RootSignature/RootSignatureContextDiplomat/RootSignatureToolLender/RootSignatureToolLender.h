#pragma once
#include "../../RootSignatureContext.h"

class RootSignatureContext::ToolLender
{
	template<typename ToolType>
	struct LicenceTypeTraits;

public:

	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_);

	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type type_)
	{
		return std::get<ToolType*>(tools);
	}


private:

	std::tuple<> tools;
};

//template<>
//struct RootSignatureContext::ToolLender::LicenceTypeTraits<RootSignatureContext::RootSignatureCreator>
//{
//	using Type = UsesRootSigCreatorLicence;
//};

