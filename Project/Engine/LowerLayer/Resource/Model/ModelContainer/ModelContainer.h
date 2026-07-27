#pragma once
#include "../ModelContext.h"

class Model;


class ModelContext::ModelContainer
{
public:

	struct AddLicence;

	ModelContainer(NexusFieldProof proof_);
	~ModelContainer();


	void Add(AddLicence addLicence_,std::unique_ptr<Model>&& model_);
	const std::vector<std::unique_ptr<Model>>& Access()const;

private:

	std::vector<std::unique_ptr<Model>> container;

};

struct ModelContext::ModelContainer::AddLicence
{
private:

	friend class ModelContext::ModelCreator;
	explicit AddLicence() = default;
};



