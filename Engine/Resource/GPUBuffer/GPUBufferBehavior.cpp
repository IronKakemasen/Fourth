#include "PreCompileHedder.h"
#include "GPUBufferBehavior.h"
#include "../../Utility/StringConnverter/StringConverter.h"

namespace
{
	std::string fileName = "GPUBufferBehavior.cpp";
}

GPUBufferBehavior::GPUBufferBehavior(const InstanceKey& instanceKey, std::string name_,
	Microsoft::WRL::ComPtr<ID3D12Resource> resource1_, Microsoft::WRL::ComPtr<ID3D12Resource> resource2_) : name(name_), resources{ {std::move(resource1_), std::move(resource2_)} }
{

}

ID3D12Resource& GPUBufferBehavior::GetResource(const BufferAccessKey& bufferAccessKey_ ,int index_)
{
	std::string errorMsg = name + "は空です (GetResourceに失敗)";
	ErrorMessageOutput::Assert::DetectError((resources[index_] == nullptr), errorMsg , fileName);

	return *resources[index_].Get();
}

void GPUBufferBehavior::SetName(const InstanceKey& instanceKey)
{
	for (size_t i = 0; i < resources.size(); ++i)
	{
		std::string errorMsg = name + "は空です";
		ErrorMessageOutput::Assert::DetectError((resources[i] == nullptr), errorMsg, fileName);

		resources[i]->SetName(StringConverter::ConvertString(name + "[ " + std::to_string(i) + " ]").c_str());
	}
}