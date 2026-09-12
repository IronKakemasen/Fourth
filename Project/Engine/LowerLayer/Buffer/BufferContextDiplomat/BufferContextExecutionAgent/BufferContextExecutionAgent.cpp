#include "PreCompileHeader.h"
#include "BufferContextExecutionAgent.h"
#include "../../BufferCreateTools/BufferUploader/BufferUploader.h"
#include "../../GlobalConstantBuffers/GlobalConstantBuffers.h"

BufferContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	BufferContext* bufferContext_,
	BufferContext::BufferUploader* bufferUploader_,
	GlobalConstantBuffers* worldConstantBuffers_
):bufferContext(bufferContext_), bufferUploader(bufferUploader_), globalConstantBuffers(worldConstantBuffers_)
{

}

void BufferContext::ExecutionAgent::DeleteBufferUploader(NexusFieldProof proof_)
{
	bufferContext->DeleteBufferUploader(proof_, BufferContext::AgentKey{});
}

void BufferContext::ExecutionAgent::UploadAllBuffer(BufferContext::NexusFieldProof proof_)
{
	bufferUploader->UploadBuffer(proof_,BufferContext::AgentKey{});
}

void BufferContext::ExecutionAgent::PackRuntimeContainer(NexusFieldProof proof_)
{
	globalConstantBuffers->PackRuntimeContainer(proof_, BufferContext::AgentKey{});
}
