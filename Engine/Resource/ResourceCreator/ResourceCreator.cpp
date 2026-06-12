#include "PreCompileHedder.h"
#include "ResourceCreator.h"
#include "../../Utility/StringConnverter/StringConverter.h"



[[nodiscard]] std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>> ResourceCreator::CreateResource
(
	const D3D12_RESOURCE_DESC& resourceDesc_,
	const D3D12_HEAP_PROPERTIES& heapProperties_,
	const D3D12_CLEAR_VALUE* clearValuePtr_,
	const std::string& name_
)
{
	auto resource1 = createResourceCommand(resourceDesc_, heapProperties_, clearValuePtr_, name_);
	auto resource2 = createResourceCommand(resourceDesc_, heapProperties_, clearValuePtr_, name_);

	//命名
	resource1->SetName(StringConverter::ConvertString(name_).c_str());

	return { std::move(resource1), std::move(resource2) };
}
