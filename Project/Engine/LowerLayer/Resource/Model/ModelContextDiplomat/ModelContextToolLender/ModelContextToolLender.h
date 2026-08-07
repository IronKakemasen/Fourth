#pragma once
#include "../../ModelContext.h"

class ModelContext::ToolLender
{
	template<typename ToolType>
	struct LicenceTypeTraits;


public:

	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_);

	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools).get();
	}


private:

	std::tuple<> tools;

};


//template<>
//struct ModelContext::ToolLender::LicenceTypeTraits<ModelContext::ModelContainer>
//{
//	using Type = ModelContainerAccessLicence;
//};
//

