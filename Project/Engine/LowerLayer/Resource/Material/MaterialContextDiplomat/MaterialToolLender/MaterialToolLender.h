#pragma once
#include "../../MaterialContext.h"

class MaterialContext::ToolLender
{
	template<typename ToolType>
	struct ToolTypeTraits;

	struct AccessMaterialAttacherLicence;

public:

	template<typename ToolType>
	using LicenceType = typename ToolTypeTraits<ToolType>::Licence;

	ToolLender
	(
		NexusFieldProof proof_,
		MaterialAttacher* materialAttacher_
	);

	template<typename ToolType>
	auto& Lend(typename ToolTypeTraits<ToolType>::Licence licence_)
	{
		return *std::get<ToolType*>(tools);
	}

private:

	std::tuple
	<
		MaterialAttacher*
	>tools;

};


template<>
struct MaterialContext::ToolLender::ToolTypeTraits<MaterialContext::MaterialAttacher>
{
	using Licence = AccessMaterialAttacherLicence;
};


