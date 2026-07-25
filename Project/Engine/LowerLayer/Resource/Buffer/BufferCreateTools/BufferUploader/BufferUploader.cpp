#include "PreCompileHeader.h"
#include "BufferUploader.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

#include "BufferUploaderTools/IntermediateResourceCreator/IntermediateResourceCreator.h"
#include "BufferUploaderTools/BarrierExtractor/BarrierExtractor.h"
#include "BufferUploaderTools/BufferAndResourcePicker/BufferAndResourcePicker.h"

//外部
#include "../../../../Core/Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../../../../Core/Command/CommandContextDiplomat/CommandContextCmdProvider/CommandContextCmdProvider.h"

namespace
{
	auto const fileName = "BufferUploader.cpp";
}

BufferContext::BufferUploader::BufferUploader
(
	BufferContext::NexusFieldProof proof_,
	BufferContext::ResourceCreator* resourceCreator_,
	BufferContext::BufferDispatcher* dispatcher_,
	CommandContextDiplomat* commandContextDiplomat_
):resourceCreator(resourceCreator_), dispatcher(dispatcher_)
{
	//コマンドプロバイダーにアクセス
	auto* commandProvider = commandContextDiplomat_->Access<CommandContext::CommandProvider>();
	CommandContext::CommandProvider::PermissionType<CommandContext::ResourceUploader::UploadCommand> licence{};

	uploadCommand = commandProvider->Provide<CommandContext::ResourceUploader::UploadCommand>(licence);
	pitchBarriersCommand = commandProvider->Provide<CommandContext::ResourceUploader::PitchBarrierCommand>(licence);
}

BufferContext::BufferUploader::~BufferUploader()
{
	Logger::Log("BufferUploader Destructor Runs", fileName);
	Logger::Log("Delete: all intermediateResources(" + std::to_string((UINT)intermediateResources.size()) + ")", fileName);
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ID3D12Resource* BufferContext::BufferUploader::CreateInterMediateResource(UINT const resourceSize_)
{
	return intermediateResources.emplace_back
	(IntermediateResourceCreator::CreateInterMediateResource(resourceCreator, resourceSize_)).Get();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(GPUBufferBehavior* dstBuffer_)
{
	barriers.emplace_back(BarrierExtractor::ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(dstBuffer_));
}

template<>
void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(GPUBufferBehavior* dstBuffer_)
{
	barriers.emplace_back(BarrierExtractor::ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(dstBuffer_));
}

//Nexusフィールド限定、代行者限定
void BufferContext::BufferUploader::UploadBuffer(BufferContext::NexusFieldProof proof_, BufferContext::AgentKey agentKey_)
{
	//GPUBufferBehaviorから、IReadOnlyインターフェースにキャストしてバリアを抽出し
	///バリアをためる
	///common -> copy
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		//バッファと生リソースを取り出す
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(dstBuffer);
	}

	///上記のコマンドを流す
	Flush("Pitch All Barriers to CopyDst");

	///コピーしてアップロードする
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		uploadCommand(dstResource, data.intermediateResource, &data.subResource, 1);
	}

	///バリアをためる
	///Copy -> ShaderResource
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(dstBuffer);
	}

	///上記のコマンドを流す
	Flush("Pitch All Barriers to ShaderResource");

	//ログ出力
	EndLog();
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::tuple<GPUBufferBehavior*, ID3D12Resource*> BufferContext::BufferUploader::PickBufferAndResource(BufferUniqueID id_)const
{
	return BufferAndResourcePicker::PickBufferAndResource(dispatcher, id_);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::Flush(std::string log_)
{
	pitchBarriersCommand(barriers.data(), UINT(barriers.size()));
	Logger::Log(log_ + "(" + std::to_string((UINT)barriers.size()) + ")", fileName);
	barriers.clear();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::EndLog()const
{
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		Logger::Log("Complete Uploading: " + dstBuffer->WatchName() + "(" + std::to_string(data.resourceSize) + ")", fileName);
	}
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//template
//void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(GPUBufferBehavior* dstBuffer_);
//
//template
//void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(GPUBufferBehavior* dstBuffer_);
