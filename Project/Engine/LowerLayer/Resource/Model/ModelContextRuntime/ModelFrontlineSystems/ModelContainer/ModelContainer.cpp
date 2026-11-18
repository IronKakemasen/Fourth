#include "PreCompileHeader.h"
#include "ModelContainer.h"
#include "ModelSeparator/ModelSeparator.h"

namespace
{
	auto const fileName = "ModelContainer.cpp";
}

ModelContext::FrontlineSystems::ModelContainer::ModelContainer(NexusFieldProof proof_)
{

}

ModelContext::FrontlineSystems::ModelContainer::~ModelContainer()
{

}

void ModelContext::FrontlineSystems::ModelContainer::SeparateModels(Local_InitLicence licence_)
{
	ModelSeparator modelSeparator;

	separatedByRenderState = modelSeparator.SeparateAllModels(container);

	Logger::Log("Model Separating comp", fileName);
}

template<Model::MeshUpdateType type>
void ModelContext::FrontlineSystems::ModelContainer::Add(Local_InitLicence licence_, std::unique_ptr<Model>&& model_)
{
	auto* model = container.emplace_back(std::move(model_)).get();
	//Static/Dynamic別で仕分ける
	separatedByModelType[UINT(type)].emplace_back(model);

#ifdef _DEBUG

	if constexpr (type == Model::MeshUpdateType::kStatic)
	{
		Logger::Log("Add: " + model->WatchName() + "to Static Container", fileName);
	}
	else if constexpr (type == Model::MeshUpdateType::kDynamic)
	{
		Logger::Log("Add: " + model->WatchName() + "to Static kDynamic", fileName);
	}

#endif // _DEBUG

}

template
void ModelContext::FrontlineSystems::ModelContainer::Add<Model::MeshUpdateType::kStatic>(Local_InitLicence licence_, std::unique_ptr<Model>&& model_);
template
void ModelContext::FrontlineSystems::ModelContainer::Add<Model::MeshUpdateType::kDynamic>(Local_InitLicence licence_, std::unique_ptr<Model>&& model_);
