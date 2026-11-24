#include "PreCompileHeader.h"
#include "DebugContextDiplomat.h"
#include "DebugExecutionAgent/DebugExecutionAgent.h"

DebugContextDiplomat::DebugContextDiplomat
(
	DebugContext::NexusFieldProof proof_,
	std::unique_ptr<DebugContext::ExecutionAgent>&& executionAgent_
)
{
	std::get<std::unique_ptr<DebugContext::ExecutionAgent>>(tools) = std::move(executionAgent_);
}

DebugContextDiplomat::~DebugContextDiplomat()
{

}

