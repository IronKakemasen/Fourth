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

void ModelContext::ModelContainer::Add(Local_AddLicence addLicence_, std::unique_ptr<Model>&& model_)
{
	const auto& model =  container.emplace_back(std::move(model_));
	Logger::Log("Add: " + model->WatchName(), fileName);
}

ModelContextCmds::WatchModelContainer ModelContext::ModelContainer::WatchDataCmd(ProviderKey key_)const
{
	return [this]()
	{
		return &this->container;
	};

}