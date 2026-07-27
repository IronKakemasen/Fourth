#pragma once
#include "../MeshContext.h"

class Model;


class MeshContext::ModelContainer
{
public:

	struct AddLicence;

	ModelContainer(NexusFieldProof proof_);

	void Add(AddLicence addLicence_,std::unique_ptr<Model>&& model_);
	const std::vector<std::unique_ptr<Model>>& Access()const;

private:

	std::vector<std::unique_ptr<Model>> modelContainer;

};

struct MeshContext::ModelContainer::AddLicence
{
private:

	friend class MeshContext::ModelCreator;
	explicit AddLicence() = default;
};



