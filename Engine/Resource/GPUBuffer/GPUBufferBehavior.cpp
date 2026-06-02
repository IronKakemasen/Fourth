#include "PreCompileHedder.h"
#include "GPUBufferBehavior.h"
#include "../../Utility/StringConnverter/StringConverter.h"


GPUBufferBehavior::GPUBufferBehavior(const CreateKey& createKey_ , std::string name_) : name(name_)
{

}

ID3D12Resource& GPUBufferBehavior::GetResource(const BufferAccessKey& bufferAccessKey_ ,int index_)
{
	std::string errorMsg = name + "は空です (GetResourceに失敗)";
	ErrorMessageOutput::Assert::DetectError((resources[index_] == nullptr), errorMsg , "GPUBufferBehavior.cpp");

	return *resources[index_].Get();
}

void GPUBufferBehavior::SetName(const CreateKey& createKey_)
{
	for (size_t i = 0; i < resources.size(); ++i)
	{
		std::string errorMsg = name + "は空です";
		ErrorMessageOutput::Assert::DetectError((resources[i] == nullptr), errorMsg, "GPUBufferBehavior.cpp");

		resources[i]->SetName(StringConverter::ConvertString(name + "[ " + std::to_string(i) + " ]").c_str());
	}
}