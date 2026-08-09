#include "PreCompileHeader.h"
#include "GlobalConstantBufferCreator.h"
#include "../GlobalConstantBuffers.h"
#include "../../BufferCreateTools/BufferCreator.h"
#include "../../BufferDefinition/GPUBuffer/ConstantBuffer/ConstantBuffer.h"
#include "../../BufferDefinition/BufferDescriptions/ConstantBufferDescription/ConstantBufferDescription.h"

namespace
{
	auto const fileName = "GlobalConstantBufferCreator.cpp";
}

BufferContext::GlobalConstantBufferCreator::GlobalConstantBufferCreator
(
	NexusFieldProof proof_,
	GlobalConstantBuffers* globalConstantBuffers_,
	BufferCreator* creator_
):globalConstantBuffers(globalConstantBuffers_), creator(creator_)
{

}

std::pair<BufferUniqueID, ConstantBuffer*> BufferContext::GlobalConstantBufferCreator::Create
(std::string name_, UINT const realDataSize_, ConstantBuffers::BindSlot const bindSlot_)
{

	ConstantBufferDescription desc(realDataSize_);

	//バッファユニークIDとコンスタントバッファ
	auto id_buffer = creator->CreateWithBuffer(desc, name_);

	globalConstantBuffers->Import
	(
		GlobalConstantBuffers::Local_ImportLicence{},
		id_buffer.second->WatchName(),
		(UINT)bindSlot_,
		{
			id_buffer.second->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 0)->GetGPUVirtualAddress(),
			id_buffer.second->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 1)->GetGPUVirtualAddress()
		}
	);

	return id_buffer;
}

BufferContextCmds::CreateCBufferCmd BufferContext::GlobalConstantBufferCreator::ProvideCreateCBufferCmd(ProviderKey key_)
{
	return [this](std::string name_, UINT const realDataSize_, ConstantBuffers::BindSlot const bindSlot_)
	{
		return Create(name_, realDataSize_, bindSlot_);
	};
}



