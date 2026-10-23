#include "PreCompileHeader.h"
#include "RenderContextDiplomat.h"
#include "RenderContextExecutionAgent/RenderContextExecutionAgent.h"


RenderContextDiplomat::RenderContextDiplomat
(
	RenderContext::NexusFieldProof proof_,
	std::unique_ptr<RenderContext::ExecutionAgent>&& agent_
)
{
	std::get<std::unique_ptr<RenderContext::ExecutionAgent>>(tools) = std::move(agent_);
}
