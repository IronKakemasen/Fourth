
#include "ResourceCreator.h"
#include "../../../../../Utility/StringConnverter/StringConverter.h"


BufferContext::ResourceCreator::ResourceCreator(BufferContext::InstanceKey instanceKey_, BufferContext::CreateResourceCommand createResourceCommand_)
	: createResourceCommand(createResourceCommand_) 
{

}

BufferContext::ResourceCreator::ResourceCreator::~ResourceCreator()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] BufferContext::ResourceCreator::ResourceContainer BufferContext::ResourceCreator::Create
(
	const D3D12_RESOURCE_DESC& resourceDesc_,
	const D3D12_HEAP_PROPERTIES& heapProperties_,
	const D3D12_CLEAR_VALUE* clearValuePtr_,
	D3D12_RESOURCE_STATES initialState_,
	const std::string& name_,
	int numResource_
)
{
	ResourceContainer resourceContainer;

	for (int i = 0; i < numResource_; ++i)
	{
		//生リソース生成
		auto& resource = resourceContainer.emplace_back(createResourceCommand(resourceDesc_, heapProperties_, clearValuePtr_, initialState_, name_));
		//生リソースに名を刻む
		resource->SetName(StringConverter::ConvertString(name_ + "[ " + std::to_string(i) + "]").c_str());
	}

	return std::move(resourceContainer);
}
