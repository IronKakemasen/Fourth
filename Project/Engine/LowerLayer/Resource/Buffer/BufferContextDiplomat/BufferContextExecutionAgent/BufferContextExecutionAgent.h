#pragma once
#include "../../BufferContext.h"

class BufferContext::ExecutionAgent
{
public:
	ExecutionAgent(NexusFieldProof proof_, BufferContext* bufferContext_);

	//BufferUploaderの削除を代行
	void DeleteBufferUploader(BufferContext::NexusFieldProof proof_);

private:
	BufferContext* bufferContext;
};

