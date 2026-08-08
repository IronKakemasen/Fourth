#include "PreCompileHeader.h"
#include "BufferContextDiplomat.h"
#include "BufferToolLender/BufferToolLender.h"
#include "BufferContextExecutionAgent/BufferContextExecutionAgent.h"
#include "BufferContextCmdProvider/BufferContextCmdProvider.h"


BufferContextDiplomat::BufferContextDiplomat
(
	BufferContext::NexusFieldProof proof_,
	std::unique_ptr<BufferContext::ToolLender>&& toolLender_,
	std::unique_ptr<BufferContext::ExecutionAgent>&& executionAgent_,
	std::unique_ptr<BufferContext::CmdProvider>&& cmdProvider_

)
{
	std::get<std::unique_ptr<BufferContext::ToolLender>>(tools) = std::move(toolLender_);
	std::get<std::unique_ptr<BufferContext::ExecutionAgent>>(tools) = std::move(executionAgent_);
	std::get<std::unique_ptr<BufferContext::CmdProvider>>(tools) = std::move(cmdProvider_);


	
}
