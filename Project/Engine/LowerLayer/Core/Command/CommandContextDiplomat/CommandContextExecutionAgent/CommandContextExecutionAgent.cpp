#include "PreCompileHeader.h"
#include "CommandContextExecutionAgent.h"

#include "../../ResourceUploader/ResourceUploader.h"


CommandContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, CommandContext::ResourceUploader* resourceUploader_)
:resourceUploader(resourceUploader_)
{

}

void CommandContext::ExecutionAgent::KickAndSynchronizeUploadCommand(NexusFieldProof proof_)
{
	resourceUploader->KickAndSynchronize(proof_, CommandContext::AgentKey{});
}
