#include "PreCompileHeader.h"
#include "GPUBufferBehavior.h"
#include "../../../../Utility/StringConnverter/StringConverter.h"
#include "../BufferDescriptions/BufferDescriptionBehavior.h"
#include "../../ResourceBarrier.h"



namespace
{
	std::string fileName = "GPUBufferBehavior.cpp";
}

GPUBufferBehavior::GPUBufferBehavior
(
	const InstanceKey& instanceKey_,
	std::string name_,
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resourceContainer_,
	std::unique_ptr <BufferDescriptionBehavior>&& description_
) : name(name_), description(std::move(description_))
{
	size_t const bufferSize = resourceContainer_.size();

	buffers.resize(bufferSize);

	for (size_t i = 0;i < bufferSize;++i)
	{
		buffers[i].resource = std::move(resourceContainer_[i]);
		buffers.at(i).curResourceState = description->initialState;
	}
}
GPUBufferBehavior::~GPUBufferBehavior()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3D12_RESOURCE_BARRIER GPUBufferBehavior::Buffer::CreateBarrier(D3D12_RESOURCE_STATES after_)
{
	auto buff = curResourceState;
	curResourceState = after_;

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
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ID3D12Resource* GPUBufferBehavior::GetResource(ResourceAccessKey bufferAccessKey_ ,int resourceNo_)
{
	std::string errorMsg = name + "は空です (GetResourceに失敗)";

	ErrorMessageOutput::Assert::DetectError((buffers.at(resourceNo_).resource != nullptr), errorMsg , fileName);

	return buffers.at(resourceNo_).resource.Get();
}

