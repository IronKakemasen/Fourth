#include "PreCompileHeader.h"
#include "ModelContextExecutionAgent.h"
#include "../../CreateModelTools/ModelDataLoader/ModelDataLoader.h"


ModelContext::ExecutionAgent::ExecutionAgent
(
	ModelContext::NexusFieldProof proof_,
	ModelContext::ModelDataLoader* modelDataLoader_
): modelDataLoader(modelDataLoader_)
{
	
}

void ModelContext::ExecutionAgent::DeleteModelDataCache(ModelContext::NexusFieldProof proof_)
{
	modelDataLoader->DeleteModelDataCache(proof_, ModelContext::AgentKey{});
}