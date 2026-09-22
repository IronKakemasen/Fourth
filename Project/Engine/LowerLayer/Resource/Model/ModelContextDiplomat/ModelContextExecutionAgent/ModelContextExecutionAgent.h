#pragma once
#include "../../ModelContext.h"



class ModelContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		ModelContext::NexusFieldProof proof_,
		ModelContext& modelContext_,
		ModelContainer& modelContainer_
	);

	void DeleteModelDataCache(NexusFieldProof proof_);
	void SeparateModelContainer(NexusFieldProof proof_);

private:

	ModelContext& modelContext;
	ModelContainer& modelContainer;

};


