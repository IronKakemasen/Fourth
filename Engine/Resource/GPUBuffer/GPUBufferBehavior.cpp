#include "PreCompileHedder.h"
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
) : name(name_), resources{ {std::move(resource1_), std::move(resource2_)} }, description(std::move(description_))
{
	curState = description->initialState;
}

GPUBufferBehavior::~GPUBufferBehavior()
{

}


ID3D12Resource* GPUBufferBehavior::GetResource(BufferAccessKey bufferAccessKey_ ,int resourceNo_)
{
	std::string errorMsg = name + "は空です (GetResourceに失敗)";
	ErrorMessageOutput::Assert::DetectError((resources[resourceNo_] != nullptr), errorMsg , fileName);

	return resources[resourceNo_].Get();
}

