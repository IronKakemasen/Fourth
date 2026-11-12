#include "PreCompileHeader.h"
#include "MaterialContextDiplomat.h"
#include "MaterialToolLender/MaterialToolLender.h"
#include "MaterialExecutionAgent/MaterialExecutionAgent.h"



MaterialContextDiplomat::MaterialContextDiplomat
(
	MaterialContext::NexusFieldProof proof_,
	std::unique_ptr<MaterialContext::ExecutionAgent>&& executionAgent_,
	std::unique_ptr<MaterialContext::ToolLender>&& toolLender_
)
{
	std::get<std::unique_ptr<MaterialContext::ExecutionAgent>>(tools) = std::move(executionAgent_);
	std::get<std::unique_ptr<MaterialContext::ToolLender>>(tools) = std::move(toolLender_);
}

MaterialContextDiplomat::~MaterialContextDiplomat(){}