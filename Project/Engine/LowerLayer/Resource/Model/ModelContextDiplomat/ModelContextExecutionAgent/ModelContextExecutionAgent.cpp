#include "PreCompileHeader.h"
#include "ModelContextExecutionAgent.h"
#include "../../CreateModelTools/ModelDataLoader/ModelDataLoader.h"


ModelContext::ExecutionAgent::ExecutionAgent
(
	ModelContext::NexusFieldProof proof_,
	ModelContext& modelContext_
):modelContext(modelContext_)
{
	
}


void ModelContext::ExecutionAgent::DeleteModelDataCache(NexusFieldProof proof_)
{
	modelContext.DeleteModelDataCache(proof_, AgentKey{});
}
