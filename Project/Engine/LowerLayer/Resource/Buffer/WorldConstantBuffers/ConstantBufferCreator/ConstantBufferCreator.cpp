#include "PreCompileHeader.h"
#include "ConstantBufferCreator.h"
#include "../WorldConstantBuffers.h"
#include "../../BufferCreateTools/BufferCreator.h"
#include "../../BufferDefinition/GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../../BufferDefinition/BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"

namespace
{
	auto const fileName = "ConstantBufferCreator.cpp";
}

BufferContext::ConstantBufferCreator::ConstantBufferCreator
(
	NexusFieldProof proof_,
	WorldConstantBuffers* worldConstantBuffers_,
	BufferCreator* creator_
):worldConstantBuffers(worldConstantBuffers_), creator(creator_)
{

}

[[nodiscard]] BufferUniqueID BufferContext::ConstantBufferCreator::Create(const std::string& name_, UINT const realDataSize_, const uint8_t bindSlot_)
{

	ConstantBufferDescription desc(realDataSize_);

	//バッファユニークIDとコンスタントバッファ
	auto id_buffer = creator->CreateWithBuffer(desc, name_);


	worldConstantBuffers->Import
	(
		WorldConstantBuffers::Local_ImportLicence{},
		id_buffer.second->WatchName(),
		bindSlot_,
		{
			id_buffer.second->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 0)->GetGPUVirtualAddress(),
			id_buffer.second->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 1)->GetGPUVirtualAddress()
		}
	);

	return id_buffer.first;
}


