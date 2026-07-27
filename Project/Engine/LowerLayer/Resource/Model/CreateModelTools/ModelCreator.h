#pragma once
#include "../ModelContext.h"
#include "../ModelStructure/ModelDescription.h"

class Model;


class ModelContext::ModelCreator
{
public:

	ModelCreator
	(
		NexusFieldProof proof_, 
		std::unique_ptr<ModelContext::ModelDescAssembler>&& modelAssembler_,
		ModelContext::ModelContainer* modelContainer_
	);

	Model* Create
	(
		std::string modelFileName_, 
		const std::vector<ModelDescription::Configurable>& modelDataConfigurables_,
		std::string modelName_ = "nameLess"
	);

private:

	//生成数。ネーミング用
	UINT numCreate{};
	std::unique_ptr<ModelContext::ModelDescAssembler> modelDescAssembler;
	ModelContext::ModelContainer* modelContainer;
};

