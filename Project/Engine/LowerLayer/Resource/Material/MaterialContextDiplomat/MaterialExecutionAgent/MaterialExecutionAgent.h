#pragma once
#include "../../MaterialContext.h"

class MaterialContext::ExecutionAgent
{
public:

	ExecutionAgent
	(
		NexusFieldProof proof_,
		MaterialDataBatcher& materialDataBatcher_
	);

	void WriteMaterialIndexGroupsArrBuffer
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


private:

	MaterialDataBatcher& materialDataBatcher;

};

