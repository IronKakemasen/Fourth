#include "PreCompileHeader.h"
#include "SceneContextDiplomat.h"
#include "SceneExecutionAgent/SceneExecutionAgent.h"

SceneContextDiplomat::SceneContextDiplomat
(
	SceneContext::NexusFieldProof proof_,
	std::unique_ptr<SceneContext::ExecutionAgent>&& executionAgent_
)
{
	std::get<std::unique_ptr<SceneContext::ExecutionAgent>>(tools) = std::move(executionAgent_);

}

