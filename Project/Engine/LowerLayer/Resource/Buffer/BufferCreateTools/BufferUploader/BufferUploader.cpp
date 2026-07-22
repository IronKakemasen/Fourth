#include "PreCompileHeader.h"
#include "BufferUploader.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

//ツール
#include "../ResourceCreator/ResourceCreator.h"
#include "../../RuntimeBufferManagementSystems/BufferDispatcher/BufferDispatcher.h"

//外部
#include "../../../../Core/Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../../../../Core/Command/CommandContextDiplomat/CommandContextCmdProvider/CommandContextCmdProvider.h"

namespace
{
	auto const fileName = "BufferUploader.cpp";
}

BufferContext::BufferUploader::BufferUploader
(
	BufferContext::InstanceKey key_,
	BufferContext::ResourceCreator* resourceCreator_,
	BufferContext::BufferDispatcher* dispatcher_,
	CommandContextDiplomat* commandContextDiplomat_
):resourceCreator(resourceCreator_), dispatcher(dispatcher_)
{
	//コマンドプロバイダーにアクセス
	auto* commandProvider = commandContextDiplomat_->Access<CommandContext::CommandProvider>();
	uploadCommand = commandProvider->ProvideResourceUploadCommand(CommandContext::CommandProvider::UsesResourceUploadCmdPermission{});
}

BufferContext::BufferUploader::~BufferUploader()
{
	Logger::Log("BufferUploader Destructor Runs", fileName);
	Logger::Log("Delete: intermediateResources", fileName);
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ID3D12Resource* BufferContext::BufferUploader::CreateInterMediateResource(UINT resourceSize_)
{
	//中間リソース作成
	auto& intermedRes = intermediateResources.emplace_back
	(
		std::move
		(
			resourceCreator->Create
			(
				CreateIntermedeiteResourceDesc(resourceSize_),
				CreateIntermedeiteHeapProp(),
				nullptr,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				"intermed" + std::to_string(UINT(intermediateResources.size())),
				1
			)[0]
		)
	);

	return intermedRes.Get();
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



