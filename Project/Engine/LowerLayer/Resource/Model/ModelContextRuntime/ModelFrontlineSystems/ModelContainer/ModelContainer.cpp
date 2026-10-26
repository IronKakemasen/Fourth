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

void ModelContext::FrontlineSystems::ModelContainer::Add(Local_InitLicence licence_, std::unique_ptr<Model>&& model_)
{
	const auto& model =  container.emplace_back(std::move(model_));
	Logger::Log("Add: " + model->WatchName(), fileName);
}


void ModelContext::FrontlineSystems::ModelContainer::SeparateModels(Local_InitLicence licence_)
{
	ModelSeparator modelSeparator;

	auto output = modelSeparator.SeparateAllModels(container);
	separatedByRenderState = std::move(output.first);
	separatedByModelType = std::move(output.second);

	Logger::Log("Model Separating comp", fileName);
}

