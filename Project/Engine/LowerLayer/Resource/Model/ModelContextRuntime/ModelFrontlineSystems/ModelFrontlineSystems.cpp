#include "PreCompileHeader.h"
#include "ModelFrontlineSystems.h"
#include "ModelContainer/ModelContainer.h"

namespace
{
	auto const fileName = "ModelFrontlineSystems.h";
}

ModelContext::FrontlineSystems::FrontlineSystems(NexusFieldProof proof_, ModelCreator& modelCreator_)
	:modelCreator(modelCreator_)
{
	modelContainer.reset(new ModelContainer(proof_));
	Logger::Log("Instantiate: modelContainer", fileName);

}

ModelContext::FrontlineSystems::~FrontlineSystems()
{

}

template<Model::Type modelType>
void ModelContext::FrontlineSystems::UpdateModelTransform()
{

	auto const& models = modelContainer->WatchSeparatedByModelType()[(UINT)modelType];
	for (auto* model : models)
	{
		auto refTransforms = model->RefTransforms();
		for (auto& trans : refTransforms)
		{
			trans.Update();
		}
	}
}


std::vector<Model*> ModelContext::FrontlineSystems::AddModel(std::vector<std::unique_ptr<Model>>&& modelUniques_)
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

void ModelContext::FrontlineSystems::SeparateModels()
{
	modelContainer->SeparateModels(ModelContainer::Local_InitLicence{});
}

ModelContext::FrontlineSystems::ModelContainer const* ModelContext::FrontlineSystems::WatchModelContainer()const
{
	return modelContainer.get();
}


template
void ModelContext::FrontlineSystems::UpdateModelTransform<Model::Type::kDynamic>();

template
void ModelContext::FrontlineSystems::UpdateModelTransform<Model::Type::kStatic>();
