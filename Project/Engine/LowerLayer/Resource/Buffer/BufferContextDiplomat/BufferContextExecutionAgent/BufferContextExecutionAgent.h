#pragma once
#include "../../BufferContext.h"

class BufferContext::ExecutionAgent
{
public:
	ExecutionAgent
	(
		NexusFieldProof proof_,
		BufferContext* bufferContext_,
		BufferUploader* bufferUploader_,
		WorldConstantBuffers* worldConstantBuffers_
	);

	//BufferUploaderの削除を代行
	void DeleteBufferUploader(NexusFieldProof proof_);
	//Resourceのバリアを全て張るのを代行
	void UploadAllBuffer(NexusFieldProof proof_);
	//ワールド定数バッファのコンテナクラスの移し替えを代行
	void PackRuntimeContainer(NexusFieldProof proof_);


private:
	BufferContext* bufferContext;
	BufferUploader* bufferUploader;
	WorldConstantBuffers* worldConstantBuffers;

};

