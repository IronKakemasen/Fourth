#include "PreCompileHeader.h"
#include "ModelContainer.h"
#include "../ModelStructure/Model.h"
#include "ModelSeparator/ModelSeparator.h"

namespace
{
	auto const fileName = "ModelContainer.cpp";
}

ModelContext::ModelContainer::ModelContainer(NexusFieldProof proof_)
{

}

ModelContext::ModelContainer::~ModelContainer()
{

}

void ModelContext::ModelContainer::Add(Local_AddLicence addLicence_, std::unique_ptr<Model>&& model_)
{
	const auto& model =  container.emplace_back(std::move(model_));
	Logger::Log("Add: " + model->WatchName(), fileName);
}

ModelContextCmds::WatchModelContainer ModelContext::ModelContainer::WatchModelDataCmd(ProviderKey key_)const
{
	return [this]()
	{
		return &this->container;
	};
}

ModelContextCmds::WatchSeparatedByRenderState ModelContext::ModelContainer::WatchSeparatedByRenderStateCmd(ProviderKey key_)
{
	return [this]()
	{
		return &this->separatedByRenderState;
	};
}

void ModelContext::ModelContainer::SeparateModels(NexusFieldProof proof_, AgentKey key_)
{
	ModelSeparator modelSeparator(proof_, key_);

	auto output = modelSeparator.SeparateAllModels(container);
	separatedByRenderState = std::move(output.first);
	separatedByModelType = std::move(output.second);

	Logger::Log("Model Separating comp", fileName);
}

