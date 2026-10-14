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

void ModelContext::ModelFrontlineSystems::AddModel(std::unique_ptr<Model>&& model_)
{
	modelContainer->Add(ModelContainer::Local_InitLicence{}, std::move(model_));
}

void ModelContext::ModelFrontlineSystems::SeparateModels()
{
	modelContainer->SeparateModels(ModelContainer::Local_InitLicence{});
}
