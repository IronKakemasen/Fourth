#include "PreCompileHeader.h"
#include "MeshContextDiplomat.h"
#include "MeshContextExecutionAgent/MeshContextExecutionAgent.h"



MeshContextDiplomat::MeshContextDiplomat
(
	MeshContext::NexusFieldProof proof_,
	std::unique_ptr<MeshContext::ExecutionAgent>&& agent_
)
{
	std::get<std::unique_ptr<MeshContext::ExecutionAgent>>(tools) = std::move(agent_);
}

