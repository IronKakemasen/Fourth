#include "PreCompileHeader.h"
#include "ResourceCreator.h"
#include "../../../Utility/StringConnverter/StringConverter.h"


BufferContext::ResourceCreator::ResourceCreator(BufferContext::InstanceKey instanceKey_, BufferContext::CreateResourceCommand createResourceCommand_)
	: createResourceCommand(createResourceCommand_) 
{

}

BufferContext::ResourceCreator::~ResourceCreator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] std::pair<Microsoft::WRL::ComPtr<ID3D12Resource>, Microsoft::WRL::ComPtr<ID3D12Resource>> BufferContext::ResourceCreator::Create
(
	const D3D12_RESOURCE_DESC& resourceDesc_,
	const D3D12_HEAP_PROPERTIES& heapProperties_,
	const D3D12_CLEAR_VALUE* clearValuePtr_,
	std::array<D3D12_RESOURCE_STATES, ProjectConfig::Render::kRequiredGPUBufferSum> initialStates_,
	const std::string& name_
)
{
	auto resource1 = createResourceCommand(resourceDesc_, heapProperties_, clearValuePtr_, initialStates_.at(0), name_);
	auto resource2 = createResourceCommand(resourceDesc_, heapProperties_, clearValuePtr_, initialStates_.at(1),name_);

	//命名
	resource1->SetName(StringConverter::ConvertString(name_ + "[0]").c_str());
	resource2->SetName(StringConverter::ConvertString(name_ + "[1]").c_str());

	return { std::move(resource1), std::move(resource2) };
}
