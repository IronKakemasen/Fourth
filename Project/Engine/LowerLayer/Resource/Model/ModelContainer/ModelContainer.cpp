#include "PreCompileHeader.h"
#include "ModelContainer.h"
#include "../ModelStructure/Model.h"


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

void ModelContext::ModelContainer::Add(AddLicence addLicence_, std::unique_ptr<Model>&& model_)
{
	const auto& model =  container.emplace_back(std::move(model_));
	Logger::Log("Add: " + model->WatchName(), fileName);
}

const std::vector<std::unique_ptr<Model>>& ModelContext::ModelContainer::Access()const
{
	return container;
}