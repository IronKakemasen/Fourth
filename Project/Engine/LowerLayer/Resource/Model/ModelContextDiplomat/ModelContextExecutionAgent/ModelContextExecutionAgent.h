#pragma once
#include "../../ModelContext.h"



class ModelContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		ModelContext::NexusFieldProof proof_,
		ModelContext& modelContext_
	);

	void DeleteModelDataCache(NexusFieldProof proof_);

private:

	ModelContext& modelContext;

};


