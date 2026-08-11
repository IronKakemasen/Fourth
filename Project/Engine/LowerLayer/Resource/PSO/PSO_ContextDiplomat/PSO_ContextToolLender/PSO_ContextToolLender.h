#pragma once
#include "../../PSO_Context.h"


class PSO_Context::ToolLender
{
	template<typename ToolType>
	struct LicenceTypeTraits;

	struct UsesPSO_CreatorLicence;

public:

	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_,PSO_Creator* creator_);

	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools);
	}

private:

	std::tuple<PSO_Creator*> tools;

};

template<>
struct PSO_Context::ToolLender::LicenceTypeTraits<PSO_Context::PSO_Creator>
{
	using Type = UsesPSO_CreatorLicence;
};
