#pragma once
#include "../../ModelContext.h"



class ModelContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		ModelContext::NexusFieldProof proof_,
		ModelContext::ModelDataLoader* modelDataLoader_
	);

	void DeleteModelDataCache(ModelContext::NexusFieldProof proof_);

private:
	ModelContext::ModelDataLoader* modelDataLoader;
};

