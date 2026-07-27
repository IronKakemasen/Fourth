#pragma once
#include "../MeshContext.h"
#include "../Model/ModelDescription.h"

class Model;

class MeshContext::ModelCreator
{
public:

	ModelCreator(NexusFieldProof proof_, std::unique_ptr<MeshContext::ModelDescAssembler>&& modelAssembler_);

	Model* Create
	(
		std::string modelFileName_, 
		const std::vector<ModelDescription::Configurable>& modelDataConfigurables_,
		std::string modelName_ = "nameLess"
	);

private:

	std::unique_ptr<MeshContext::ModelDescAssembler> ModelDescAssembler;

};

