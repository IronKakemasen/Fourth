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

	void WriteInMaterialIndexGroupsArrBuffer
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


private:

	MaterialDataBatcher& materialDataBatcher;

};

