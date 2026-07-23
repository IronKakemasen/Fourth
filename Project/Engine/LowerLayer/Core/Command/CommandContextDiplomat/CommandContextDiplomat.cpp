#include "PreCompileHeader.h"
#include "CommandContextDiplomat.h"

#include "CommandContextToolLender/CommandContextToolLender.h"
#include "CommandContextCmdProvider/CommandContextCmdProvider.h"
#include "CommandContextExecutionAgent/CommandContextExecutionAgent.h"

namespace
{
	auto const fileName = "CommandContextDiplomat.cpp";
}

CommandContextDiplomat::CommandContextDiplomat
(
	CommandContext::NexusFieldProof proof_,
	std::unique_ptr<CommandContext::CommandProvider>&& cmdProvider_,
	std::unique_ptr<CommandContext::ToolLender>&& toolLender_,
	std::unique_ptr<CommandContext::ExecutionAgent>&& executionAgent_

)
{
	std::get<std::unique_ptr<CommandContext::CommandProvider>>(tools) = std::move(cmdProvider_);
	std::get<std::unique_ptr<CommandContext::ToolLender>>(tools) = std::move(toolLender_);
	std::get<std::unique_ptr<CommandContext::ExecutionAgent>>(tools) = std::move(executionAgent_);

	
}
