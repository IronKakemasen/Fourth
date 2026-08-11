#include "PreCompileHeader.h"
#include "PSO_ContextDiplomat.h"
#include "PSO_ContextToolLender/PSO_ContextToolLender.h"



PSO_ContextDiplomat::PSO_ContextDiplomat
(
	PSO_Context::NexusFieldProof proof_,
	std::unique_ptr<PSO_Context::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<PSO_Context::ToolLender>>(tools) = std::move(toolLender_);
}
