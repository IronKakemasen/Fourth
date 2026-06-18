#include "PreCompileHeader.h"
#include "GPUBufferBehavior.h"
#include "../../Utility/StringConnverter/StringConverter.h"
#include "../BufferDescriptions/BufferDescriptionBehavior.h"
#include "../ResourceBarrier.h"



namespace
{
	std::string fileName = "GPUBufferBehavior.cpp";
}

D3D12_RESOURCE_BARRIER GPUBufferBehavior::Buffer::CreateBarrier(D3D12_RESOURCE_STATES after_)
{
	auto buff = curState;
	curState = after_;

	return ResourceBarrier::Create
	(
		resource.Get(),
		D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		D3D12_RESOURCE_BARRIER_FLAG_NONE,
		buff,
		after_,
		D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES
	);
}

GPUBufferBehavior::GPUBufferBehavior
(
	const InstanceKey& instanceKey_,
	std::string name_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource1_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource2_,
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : name(name_), description(std::move(description_))
{
	buffers.at(0).resource = std::move(resource1_);
	buffers.at(1).resource = std::move(resource2_);

	for (size_t i = 0; i < buffers.size(); ++i)
	{
		buffers.at(i).curState = description->initialStates.at(i);
	}

}
GPUBufferBehavior::~GPUBufferBehavior()
{

}


ID3D12Resource* GPUBufferBehavior::GetResource(ResourceAccessKey bufferAccessKey_ ,int resourceNo_)
{
	std::string errorMsg = name + "は空です (GetResourceに失敗)";

	ErrorMessageOutput::Assert::DetectError((buffers.at(resourceNo_).resource != nullptr), errorMsg , fileName);

	return buffers.at(resourceNo_).resource.Get();
}


D3D12_RESOURCE_BARRIER GPUBufferBehavior::CreateBarrier(ExtracteMaterialKey key_, D3D12_RESOURCE_STATES after_ , uint8_t index_)
{
	return buffers.at(index_).CreateBarrier(after_);
}