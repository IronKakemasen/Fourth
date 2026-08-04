#pragma once
#include "../../RootSignatureContext.h"

class RootSignatureContext::ToolLender
{
	template<typename ToolType>
	struct LicenceTypeTraits;

	struct UsesRootSigCreatorLicence;

public:

	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_, RootSignatureCreator* creator_);

	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type type_)
	{
		return std::get<ToolType*>(tools);
	}


private:

	std::tuple<RootSignatureCreator*> tools;
};

template<>
struct RootSignatureContext::ToolLender::LicenceTypeTraits<RootSignatureContext::RootSignatureCreator>
{
	using Type = UsesRootSigCreatorLicence;
};

