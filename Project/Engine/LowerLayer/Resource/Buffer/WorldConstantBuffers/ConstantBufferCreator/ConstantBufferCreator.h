#pragma once
#include "../../BufferContext.h"

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

	//データのコピーは他者にやってもらいたいから、バッファユニークIDを渡す
	[[nodiscard]] std::pair<BufferUniqueID, ConstantBuffer*>
		Create(const std::string& name_, UINT const realDataSize_, const uint8_t bindSlot_);


private:

	BufferCreator* creator;
	WorldConstantBuffers* worldConstantBuffers;

};

