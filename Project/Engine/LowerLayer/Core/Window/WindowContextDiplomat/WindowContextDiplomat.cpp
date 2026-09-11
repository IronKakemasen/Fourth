#include "PreCompileHeader.h"
#include "WindowContextDiplomat.h"
#include "WindowContextToolLender/WindowContextToolLender.h"
#include "WindowContextExecutionAgent/WindowContextExecutionAgent.h"

WindowContextDiplomat::WindowContextDiplomat
(
	WindowContext::NexusFieldProof proof_,
	std::unique_ptr<WindowContext::ToolLender>&& toolLender_,
	std::unique_ptr<WindowContext::ExecutionAgent>&& executionAgent_
)
{
	std::get<std::unique_ptr<WindowContext::ToolLender>>(tools) = std::move(toolLender_);
	std::get<std::unique_ptr<WindowContext::ExecutionAgent>>(tools) = std::move(executionAgent_);

}
