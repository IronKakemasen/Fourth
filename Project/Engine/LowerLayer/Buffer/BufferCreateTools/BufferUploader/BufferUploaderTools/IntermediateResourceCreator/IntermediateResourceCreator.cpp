#include "PreCompileHeader.h"
#include "IntermediateResourceCreator.h"
#include "../../../ResourceCreator/ResourceCreator.h"

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> BufferContext::BufferUploader::IntermediateResourceCreator::CreateInterMediateResource
(
	BufferContext::ResourceCreator* resourceCreator_,
	UINT resourceSize_
)
{
	//中間リソース作成
	return resourceCreator_->Create
	(
		CreateIntermedeiteResourceDesc(resourceSize_),
		CreateIntermedeiteHeapProp(),
		nullptr,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		"intermed" + std::to_string(createNum++),
		1
	)[0];
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3D12_RESOURCE_DESC BufferContext::BufferUploader::IntermediateResourceCreator::CreateIntermedeiteResourceDesc(UINT resourceSize_)
{
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = resourceSize_;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	return resourceDesc;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3D12_HEAP_PROPERTIES BufferContext::BufferUploader::IntermediateResourceCreator::CreateIntermedeiteHeapProp()
{
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;

	return heapProperties;
}

