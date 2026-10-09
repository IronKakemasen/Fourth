#include "PreCompileHeader.h"
#include "CameraContextDiplomat.h"
#include "CameraContextExecutionAgent/CameraContextExecutionAgent.h"

CameraContextDiplomat::CameraContextDiplomat
(
	CameraContext::NexusFieldProof proof_,
	std::unique_ptr<CameraContext::ExecutionAgent>&& executionAgent_
)
{
	std::get<std::unique_ptr<CameraContext::ExecutionAgent>>(tools) = std::move(executionAgent_);
}
