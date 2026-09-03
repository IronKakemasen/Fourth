#pragma once
#include "../../ModelContext.h"

class ModelContext::ToolLender
{
	template<typename ToolType>
	struct CmdTypeTraits;


public:

	template<typename ToolType>
	using LicenceType = typename CmdTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_);

	template<typename ToolType>
	auto* Lend(typename CmdTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools).get();
	}


private:

	std::tuple<> tools;

};


//template<>
//struct ModelContext::ToolLender::CmdTypeTraits<ModelContext::ModelContainer>
//{
//	using Type = ModelContainerAccessLicence;
//};
//

