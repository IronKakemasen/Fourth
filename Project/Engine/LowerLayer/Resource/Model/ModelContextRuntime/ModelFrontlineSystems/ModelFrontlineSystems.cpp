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


void ModelContext::FrontlineSystems::InputMaterialStandard(std::string const& modelFileName_, Model& model_)
{
	modelCreator.InputMaterialStandard(modelFileName_, model_);
}


template<Model::MeshUpdateType modelType>
void ModelContext::FrontlineSystems::UpdateModelTransform()
{
	auto& models = modelContainer->RefSeparatedByModelType <modelType>();
	for (auto* model : models)
	{
		auto refTransforms = model->RefTransforms();
		for (auto& trans : refTransforms)
		{
			trans.Update();
		}
	}
}

template<Model::MeshUpdateType modelType>
void ModelContext::FrontlineSystems::ResetModelTransformFrameFlag()
{
	auto& models = modelContainer->RefSeparatedByModelType<modelType>();
	for (auto* model : models)
	{
		auto refTransforms = model->RefTransforms();
		for (auto& trans : refTransforms)
		{
			trans.ResetFrameFlag();
		}
	}
}

template<Model::MeshUpdateType type>
std::vector<Model*> ModelContext::FrontlineSystems::AddModel(std::vector<std::unique_ptr<Model>>&& modelUniques_)
{
	std::vector<Model*> modelsPtr;
	modelsPtr.reserve(modelUniques_.size());

	for (auto itr = modelUniques_.begin();itr != modelUniques_.end();++itr)
	{
		modelsPtr.emplace_back((*itr).get());
		modelContainer->Add<type>(ModelContainer::Local_InitLicence{}, std::move((*itr)));
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
void ModelContext::FrontlineSystems::UpdateModelTransform<Model::MeshUpdateType::kDynamic>();
template
void ModelContext::FrontlineSystems::UpdateModelTransform<Model::MeshUpdateType::kStatic>();


template
void ModelContext::FrontlineSystems::ResetModelTransformFrameFlag<Model::MeshUpdateType::kDynamic>();
template
void ModelContext::FrontlineSystems::ResetModelTransformFrameFlag<Model::MeshUpdateType::kStatic>();

template
std::vector<Model*> ModelContext::FrontlineSystems::AddModel<Model::MeshUpdateType::kStatic>(std::vector<std::unique_ptr<Model>>&& modelUniques_);
template
std::vector<Model*> ModelContext::FrontlineSystems::AddModel<Model::MeshUpdateType::kDynamic>(std::vector<std::unique_ptr<Model>>&& modelUniques_);
