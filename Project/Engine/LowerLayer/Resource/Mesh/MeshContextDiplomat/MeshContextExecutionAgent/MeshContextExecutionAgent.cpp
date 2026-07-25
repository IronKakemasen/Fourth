#include "PreCompileHeader.h"
#include "MeshContextExecutionAgent.h"
#include "../../CreateModelTools/ModelDataLoader/ModelDataLoader.h"


MeshContext::ExecutionAgent::ExecutionAgent
(
	MeshContext::NexusFieldProof proof_,
	MeshContext::ModelDataLoader* modelDataLoader_
): modelDataLoader(modelDataLoader_)
{
	
}

void MeshContext::ExecutionAgent::DeleteModelDataCache(MeshContext::NexusFieldProof proof_)
{
	modelDataLoader->DeleteModelDataCache(proof_, MeshContext::AgentKey{});
}