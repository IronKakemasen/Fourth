#pragma once
#include "../../ModelContext.h"

class ModelContext::ToolLender
{
	template<typename ToolType>
	struct LicenceTypeTraits;


	//モデルコンテナにアクセスするための資格
	struct ModelContainerAccessLicence;

public:

	template<typename ToolType>
	using LicenceType = typename LicenceTypeTraits<ToolType>::Type;

	ToolLender(NexusFieldProof proof_, ModelContext::ModelContainer* modelContainer_);

	template<typename ToolType>
	auto* Lend(typename LicenceTypeTraits<ToolType>::Type licence_)
	{
		return std::get<ToolType*>(tools).get();
	}


private:

	std::tuple<ModelContext::ModelContainer*> tools;

};


template<>
struct ModelContext::ToolLender::LicenceTypeTraits<ModelContext::ModelContainer>
{
	using Type = ModelContainerAccessLicence;
};


