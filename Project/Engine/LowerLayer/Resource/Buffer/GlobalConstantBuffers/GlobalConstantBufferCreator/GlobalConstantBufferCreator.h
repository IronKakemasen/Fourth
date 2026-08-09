#pragma once
#include "../../BufferContext.h"
#include "../../BufferContextCmds.h"

class ConstantBuffer;

class BufferContext::GlobalConstantBufferCreator
{
public:

	GlobalConstantBufferCreator
	(
		NexusFieldProof proof_,
		GlobalConstantBuffers* globalConstantBuffers_,
		BufferCreator* creator_
	);

	//Cバッファを作成するためのコマンド
	BufferContextCmds::CreateCBufferCmd ProvideCreateCBufferCmd(ProviderKey key_);



private:

	//データのコピーは他者にやってもらいたいから、バッファユニークIDを渡す
	std::pair<BufferUniqueID, ConstantBuffer*>
		Create(std::string name_, UINT const realDataSize_, ConstantBuffers::BindSlot const bindSlot_);


	BufferCreator* creator;
	GlobalConstantBuffers* globalConstantBuffers;
};

