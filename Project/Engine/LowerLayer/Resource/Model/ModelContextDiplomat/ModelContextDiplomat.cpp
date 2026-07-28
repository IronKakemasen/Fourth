#include "PreCompileHeader.h"
#include "ModelContextDiplomat.h"
#include "ModelContextExecutionAgent/ModelContextExecutionAgent.h"
#include "ModelContextToolLender/ModelContextToolLender.h"


ModelContextDiplomat::ModelContextDiplomat
(
	ModelContext::NexusFieldProof proof_,
	std::unique_ptr<ModelContext::ExecutionAgent>&& agent_,
	std::unique_ptr<ModelContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<ModelContext::ExecutionAgent>>(tools) = std::move(agent_);
	std::get<std::unique_ptr<ModelContext::ToolLender>>(tools) = std::move(toolLender_);

}

