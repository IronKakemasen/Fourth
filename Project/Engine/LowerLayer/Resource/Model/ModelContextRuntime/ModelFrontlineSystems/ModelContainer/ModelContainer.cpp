#include "PreCompileHeader.h"
#include "ModelContainer.h"
#include "ModelSeparator/ModelSeparator.h"

namespace
{
	auto const fileName = "ModelContainer.cpp";
}

ModelContext::ModelFrontlineSystems::ModelContainer::ModelContainer(NexusFieldProof proof_)
{

}

ModelContext::ModelFrontlineSystems::ModelContainer::~ModelContainer()
{

}

void ModelContext::ModelFrontlineSystems::ModelContainer::Add(Local_InitLicence licence_, std::unique_ptr<Model>&& model_)
{
	const auto& model =  container.emplace_back(std::move(model_));
	Logger::Log("Add: " + model->WatchName(), fileName);
}


void ModelContext::ModelFrontlineSystems::ModelContainer::SeparateModels(Local_InitLicence licence_)
{
	ModelSeparator modelSeparator;

	auto output = modelSeparator.SeparateAllModels(container);
	separatedByRenderState = std::move(output.first);
	separatedByModelType = std::move(output.second);

	Logger::Log("Model Separating comp", fileName);
}

