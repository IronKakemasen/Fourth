#include "PreCompileHeader.h"
#include "BufferContextExecutionAgent.h"
#include "../../BufferCreateTools/BufferUploader/BufferUploader.h"
#include "../../WorldConstantBuffers/WorldConstantBuffers.h"

BufferContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	BufferContext* bufferContext_,
	BufferContext::BufferUploader* bufferUploader_,
	WorldConstantBuffers* worldConstantBuffers_
):bufferContext(bufferContext_), bufferUploader(bufferUploader_), worldConstantBuffers(worldConstantBuffers_)
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
	worldConstantBuffers->PackRuntimeContainer(proof_, BufferContext::AgentKey{});
}
