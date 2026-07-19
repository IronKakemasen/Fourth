#include "PreCompileHeader.h"
#include "BufferUploader.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

//ツール
#include "../ResourceCreator/ResourceCreator.h"
#include "../../RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"

//外部
#include "../../../../Core/Command/CommandContextCmdProvider/CommandContextCmdProvider.h"

namespace
{
	auto const fileName = "BufferUploader.cpp";
}

BufferContext::BufferUploader::BufferUploader
(
	BufferContext::InstanceKey key_,
	BufferContext::ResourceCreator* resourceCreator_,
	BufferContext::BufferDispatcher* dispatcher_,
	CommandContext* commandContext_
):resourceCreator(resourceCreator_), dispatcher(dispatcher_)
{
	uploadCommand = commandContext_->commandProvider->
		ProvideResourceUploadCommand(CommandContext::CommandProvider::UsesResourceUploadCmdPermission{});
}

BufferContext::BufferUploader::~BufferUploader()
{
	Logger::Log("BufferUploader Destructor Runs", fileName);
	Logger::Log("Delete: intermediateResources", fileName);
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::Upload
(
	BufferUniqueID id_,
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
	GPUBufferBehavior* dstBuffer = dispatcher->Dispatch(id_);
	ID3D12Resource* dstResource = dstBuffer->GetResource(GPUBufferBehavior::ResourceAccessKey{}, 0);

	//アップロードする
	uploadCommand(dstResource, intermediateResource.Get(), subeResource_, subResourceCount_);

	//中間リソースを一時保管
	intermediateResources.emplace_back(std::move(intermediateResource));
	Logger::Log("Complete Uploading: " + dstBuffer->WatchName() + "(" + std::to_string(dstResourceSize_) + ")", fileName);
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



