#include "PreCompileHeader.h"
#include "GPUBufferBehavior.h"
#include "../../Utility/StringConnverter/StringConverter.h"
#include "../BufferDescriptions/BufferDescriptionBehavior.h"


namespace
{
	std::string fileName = "GPUBufferBehavior.cpp";
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


ID3D12Resource* GPUBufferBehavior::GetResource(BufferAccessKey bufferAccessKey_ ,int resourceNo_)
{
	std::string errorMsg = name + "は空です (GetResourceに失敗)";

	ErrorMessageOutput::Assert::DetectError((buffers.at(resourceNo_).resource != nullptr), errorMsg , fileName);

	return buffers.at(resourceNo_).resource.Get();
}

