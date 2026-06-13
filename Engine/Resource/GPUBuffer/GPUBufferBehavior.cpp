#include "PreCompileHedder.h"
#include "GPUBufferBehavior.h"
#include "../../Utility/StringConnverter/StringConverter.h"
#include "../BufferDescriptions/IBufferDescription.h"



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
	std::unique_ptr <IBufferDescription>&& description_
) : name(name_), resources{ {std::move(resource1_), std::move(resource2_)} }, description(std::move(description_))
{

}

GPUBufferBehavior::~GPUBufferBehavior()
{

}


ID3D12Resource* GPUBufferBehavior::GetResource(const BufferAccessKey& bufferAccessKey_ ,int index_)
{
	std::string errorMsg = name + "は空です (GetResourceに失敗)";
	ErrorMessageOutput::Assert::DetectError((resources[index_] != nullptr), errorMsg , fileName);

	return resources[index_].Get();
}

