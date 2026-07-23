#include "PreCompileHeader.h"
#include "BufferContextExecutionAgent.h"


BufferContext::ExecutionAgent::ExecutionAgent(NexusFieldProof proof_, BufferContext* bufferContext_)
	:bufferContext(bufferContext_)
{

}

void BufferContext::ExecutionAgent::DeleteBufferUploader(NexusFieldProof proof_)
{
	bufferContext->DeleteBufferUploader(proof_, BufferContext::AgentKey{});
}