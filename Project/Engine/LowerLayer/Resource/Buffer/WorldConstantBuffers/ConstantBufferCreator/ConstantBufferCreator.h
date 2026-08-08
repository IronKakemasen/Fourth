#pragma once
#include "../../BufferContext.h"
#include "../../BufferContextCmds.h"

class ConstantBuffer;

class BufferContext::ConstantBufferCreator
{
public:

	ConstantBufferCreator
	(
		NexusFieldProof proof_,
		WorldConstantBuffers* worldConstantBuffers_,
		BufferCreator* creator_
	);

	//Cバッファを作成するためのコマンド
	BufferContextCmds::CreateCBufferCmd ProvideCreateCBufferCmd(ProviderKey key_);



private:

	//データのコピーは他者にやってもらいたいから、バッファユニークIDを渡す
	std::pair<BufferUniqueID, ConstantBuffer*>
		Create(std::string name_, UINT const realDataSize_, const uint8_t bindSlot_);


	BufferCreator* creator;
	WorldConstantBuffers* worldConstantBuffers;
};

