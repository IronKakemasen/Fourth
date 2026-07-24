#include "PreCompileHeader.h"
#include "BufferContextExecutionAgent.h"
#include "../../BufferCreateTools/BufferUploader/BufferUploader.h"

BufferContext::ExecutionAgent::ExecutionAgent
(
	NexusFieldProof proof_,
	BufferContext* bufferContext_,
	BufferContext::BufferUploader* bufferUploader_
):bufferContext(bufferContext_), bufferUploader(bufferUploader_)
{

}

void BufferContext::ExecutionAgent::DeleteBufferUploader(NexusFieldProof proof_)
{
	bufferContext->DeleteBufferUploader(proof_, BufferContext::AgentKey{});
}

void BufferContext::ExecutionAgent::PitchAllBarriersForUpload(BufferContext::NexusFieldProof proof_)
{
	bufferUploader->PitchAllBarrier(proof_,BufferContext::AgentKey{});
}