#include "PreCompileHeader.h"
#include "ModelFrontlineSystems.h"
#include "ModelContainer/ModelContainer.h"

namespace
{
	auto const fileName = "ModelFrontlineSystems.h";
}

ModelContext::ModelFrontlineSystems::ModelFrontlineSystems(NexusFieldProof proof_, ModelCreator& modelCreator_)
	:modelCreator(modelCreator_)
{
	modelContainer.reset(new ModelContainer(proof_));
	Logger::Log("Instantiate: modelContainer", fileName);

}

ModelContext::ModelFrontlineSystems::~ModelFrontlineSystems()
{

}



std::vector<Model*> ModelContext::ModelFrontlineSystems::AddModel(std::vector<std::unique_ptr<Model>>&& modelUniques_)
{
	std::vector<Model*> modelsPtr;
	modelsPtr.reserve(modelUniques_.size());

	for (auto itr = modelUniques_.begin();itr != modelUniques_.end();++itr)
	{
		modelsPtr.emplace_back((*itr).get());
		modelContainer->Add(ModelContainer::Local_InitLicence{}, std::move((*itr)));
	}

	return modelsPtr;
}

void ModelContext::ModelFrontlineSystems::SeparateModels()
{
	modelContainer->SeparateModels(ModelContainer::Local_InitLicence{});
}

ModelContext::ModelFrontlineSystems::ModelContainer const* ModelContext::ModelFrontlineSystems::WatchModelContaienr()const
{
	return modelContainer.get();
}

