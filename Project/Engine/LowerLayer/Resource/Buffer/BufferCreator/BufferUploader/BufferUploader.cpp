#include "PreCompileHeader.h"
#include "BufferUploader.h"

//ツール
#include "../ResourceCreator/ResourceCreator.h"

//外部
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"


namespace
{
	auto const fileName = "BufferUploader.cpp";
}

BufferContext::BufferUploader::BufferUploader
(
	BufferContext::InstanceKey key_,
	BufferContext::ResourceCreator* resourceCreator_,
	CommandContext* commandContext_
):resourceCreator(resourceCreator_)
{
	uploadCommand = commandContext_->ProvideResouceUploadCommand(CommandContext::UsesResourceUploadCmdPermission{});
}

BufferContext::BufferUploader::~BufferUploader()
{

}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::Upload
(
	GPUBufferBehavior* dstBuffer_,
	UINT dstResourceSize_,
	const D3D12_SUBRESOURCE_DATA* subeResource_,
	UINT subResourceCount_
)
{
	//中間リソース作成
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource = std::move
	(
		resourceCreator->Create
		(
			CreateIntermedeiteResourceDesc(dstResourceSize_),
			CreateIntermedeiteHeapProp(),
			nullptr,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			"intermed",
			1
		)[0]
	);

	//生リソースを取り出す
	ID3D12Resource* dstResource = dstBuffer_->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 0);

	//アップロードする
	uploadCommand(dstResource, intermediateResource.Get(), subeResource_, subResourceCount_);


	intermediateResources.emplace_back(std::move(intermediateResource));
	Logger::Log("Complete Uploading: " + dstBuffer_->WatchName() + "(" + std::to_string(dstResourceSize_) + ")", fileName);
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3D12_RESOURCE_DESC BufferContext::BufferUploader::CreateIntermedeiteResourceDesc(UINT resourceSize_)const
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
D3D12_HEAP_PROPERTIES BufferContext::BufferUploader::CreateIntermedeiteHeapProp()const
{
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	
	return heapProperties;
}



