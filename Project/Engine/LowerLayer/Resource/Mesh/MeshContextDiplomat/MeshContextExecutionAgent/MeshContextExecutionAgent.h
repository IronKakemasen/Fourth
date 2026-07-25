#pragma once
#include "../../MeshContext.h"



class MeshContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		MeshContext::NexusFieldProof proof_,
		MeshContext::ModelDataLoader* modelDataLoader_
	);

	void DeleteModelDataCache(MeshContext::NexusFieldProof proof_);

private:
	MeshContext::ModelDataLoader* modelDataLoader;
};

