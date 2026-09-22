#include "PreCompileHeader.h"
#include "ModelContextExecutionAgent.h"
#include "../../CreateModelTools/ModelDataLoader/ModelDataLoader.h"
#include "../../ModelContainer/ModelContainer.h"

ModelContext::ExecutionAgent::ExecutionAgent
(
	ModelContext::NexusFieldProof proof_,
	ModelContext& modelContext_,
	ModelContainer& modelContainer_
):modelContext(modelContext_), modelContainer(modelContainer_)
{
	
}


void ModelContext::ExecutionAgent::DeleteModelDataCache(NexusFieldProof proof_)
{
	modelContext.DeleteModelDataCache(proof_, AgentKey{});
}

void ModelContext::ExecutionAgent::SeparateModelContainer(NexusFieldProof proof_)
{
	modelContainer.SeparateModels(proof_, AgentKey{});
}