#pragma once
#include "../../BufferContext.h"

class BufferContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		NexusFieldProof proof_,
		BufferContext* bufferContext_,
		BufferContext::BufferUploader* bufferUploader_
	);

	//BufferUploaderの削除を代行
	void DeleteBufferUploader(BufferContext::NexusFieldProof proof_);
	//Resourceのバリアを全て張るのを代行
	void PitchAllBarriersForUpload(BufferContext::NexusFieldProof proof_);


private:
	BufferContext* bufferContext;
	BufferContext::BufferUploader* bufferUploader;
};

