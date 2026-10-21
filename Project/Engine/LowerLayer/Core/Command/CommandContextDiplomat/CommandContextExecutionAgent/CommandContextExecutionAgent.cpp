#include "PreCompileHeader.h"
#include "CommandContextExecutionAgent.h"
#include "../../ResourceUploader/ResourceUploader.h"
#include "../../RuntimeCommandController/RuntimeCommandController.h"

CommandContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	CommandContext::ResourceUploader& resourceUploader_,
	RuntimeCommandController& runtimeCommandController_
)
:resourceUploader(resourceUploader_), runtimeCommandController(runtimeCommandController_)
{

}

void CommandContext::ExecutionAgent::KickAndSynchronizeUploadCommand(NexusFieldProof proof_)
{
	resourceUploader.KickAndSynchronize(proof_, CommandContext::AgentKey{});
}

void CommandContext::ExecutionAgent::StartRecordingCommands(NexusFieldProof proof_, UINT frameIndex_)
{
	runtimeCommandController.RecordingStart(proof_, AgentKey{}, frameIndex_);
}

void CommandContext::ExecutionAgent::ExecuteCommands(NexusFieldProof proof_, UINT frameIndex_)
{
	runtimeCommandController.ExecuteCommands(proof_, AgentKey{}, frameIndex_);
}
