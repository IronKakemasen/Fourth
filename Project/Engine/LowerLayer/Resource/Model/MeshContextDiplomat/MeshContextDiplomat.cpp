#include "PreCompileHeader.h"
#include "MeshContextDiplomat.h"
#include "MeshContextExecutionAgent/MeshContextExecutionAgent.h"



MeshContextDiplomat::MeshContextDiplomat
(
	ModelContext::NexusFieldProof proof_,
	std::unique_ptr<ModelContext::ExecutionAgent>&& agent_
)
{
	std::get<std::unique_ptr<ModelContext::ExecutionAgent>>(tools) = std::move(agent_);
}

