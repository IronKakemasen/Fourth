#include "PreCompileHeader.h"
#include "ModelContainer.h"
#include "../Model/Model.h"


MeshContext::ModelContainer::ModelContainer(NexusFieldProof proof_)
{

}

void MeshContext::ModelContainer::Add(AddLicence addLicence_, std::unique_ptr<Model>&& model_)
{

}

const std::vector<std::unique_ptr<Model>>& MeshContext::ModelContainer::Access()const
{
	return modelContainer;
}