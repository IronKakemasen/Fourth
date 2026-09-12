#include "PreCompileHeader.h"
#include "BufferUploader.h"
#include "../../BufferDefinition/GPUBuffer/GPUBufferBehavior.h"

#include "BufferUploaderTools/IntermediateResourceCreator/IntermediateResourceCreator.h"
#include "BufferUploaderTools/BarrierExtractor/BarrierExtractor.h"
#include "BufferUploaderTools/BufferAndResourcePicker/BufferAndResourcePicker.h"

//外部
#include "../../../Core/Command/CommandContextDiplomat/CommandContextDiplomat.h"
#include "../../../Core/Command/CommandContextDiplomat/CommandContextCmdProvider/CommandContextCmdProvider.h"
#include "../../../Core/Command/CommandContextDiplomat/CommandContextCmdProvider/CommandContextCmdProviderLicences.h"

//外部
#include "../../../Core/Device/DeviceContextCmds.h"
#include "../../../Core/Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../../../Core/Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCmdLicences.h"
#include "../../../Core/Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"


namespace
{
	auto const fileName = "BufferUploader.cpp";
}

BufferContext::BufferUploader::BufferUploader
(
	BufferContext::NexusFieldProof proof_,
	BufferContext::ResourceCreator* resourceCreator_,
	BufferContext::BufferDispatcher* dispatcher_,
	CommandContextDiplomat& commandContextDiplomat_,
	DeviceContextDiplomat& deviceContextDiplomat_
):resourceCreator(resourceCreator_), dispatcher(dispatcher_)
{
	//CommandContextのコマンドプロバイダーからコマンドをもらう
	auto* commandProvider = commandContextDiplomat_.Access<CommandContext::CommandProvider>();
	CommandContext::CommandProvider::LicenceType<CommandContextCmds::UploadBufferCommand> licence{};

	//生リソースをアップロードするため
	uploadCommand = commandProvider->Provide<CommandContextCmds::UploadBufferCommand>(licence);
	//リソースのバリアを張るため
	pitchBarriersCommand = commandProvider->Provide<CommandContextCmds::PitchBarrierCommand>(licence);

	//DeviceContextのコマンドプロバイダーからコマンドをもらう
	auto* deviceContextCmdProvider = deviceContextDiplomat_.Access<DeviceContext::CommandProvider>();
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::PrepareUploadCommand> licencePrepareUpload;
	//テクスチャバッファのサブリソースを作成するため
	prepareUploadCommand = deviceContextCmdProvider->Provide<DeviceContextCmds::PrepareUploadCommand>(licencePrepareUpload);
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
	//本体は保管して、あとで破棄する。
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

template<>
void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_GENERIC_READ>(GPUBufferBehavior* dstBuffer_)
{
	barriers.emplace_back(BarrierExtractor::ExtractBarrier<D3D12_RESOURCE_STATE_GENERIC_READ>(dstBuffer_));
}

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nexusフィールド限定、代行者限定
void BufferContext::BufferUploader::UploadBuffer(BufferContext::NexusFieldProof proof_, BufferContext::AgentKey agentKey_)
{
	//GPUBufferBehaviorから、IReadOnlyインターフェースにキャストしてバリアを抽出し
	///バリアをためる[普通のバッファ]
	///common -> copy
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		//バッファと生リソースを取り出す
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(dstBuffer);
	}

	///上記のコマンドを流す
	Flush("Pitch All Barriers to CopyDst");

	///中間リソースにコピーしてアップロードする
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		uploadCommand(dstResource, data.intermediateResource, &data.subResource, 1);
	}

	///テクスチャバッファも同様にコピーしてアップロード
	for (auto& data : temporaryTextureBufferInfoStorageContainer)
	{
		//バッファと生リソースを取り出す
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		uploadCommand(dstResource, data.intermediateResource, data.subResources.data(), (UINT)data.subResources.size());
	}

	///バリアをためる
	///Copy -> ShaderResource
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(dstBuffer);
	}

	///テクスチャバッファも同様にバリアため
	for (auto& data : temporaryTextureBufferInfoStorageContainer)
	{
		//バッファと生リソースを取り出す
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		ExtractBarrier<D3D12_RESOURCE_STATE_GENERIC_READ>(dstBuffer);
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
	if (barriers.empty()) return;

	pitchBarriersCommand(barriers.data(), UINT(barriers.size()));
	Logger::Log(log_ + "(" + std::to_string((UINT)barriers.size()) + ")", fileName);
	barriers.clear();
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::EndLog()const
{
	Logger::Log("===== Size Of DataType x numDataContains =====");
	for (auto& data : temporaryBufferInfoStorageContainer)
	{
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		Logger::Log("Complete Uploading: " + dstBuffer->WatchName() + "(" + std::to_string(data.dataSize) + " x " + std::to_string(data.numData) + ")", fileName);
	}

	for (auto& data : temporaryTextureBufferInfoStorageContainer)
	{
		auto [dstBuffer, dstResource] = PickBufferAndResource(data.id);
		Logger::Log("Complete Uploading: " + dstBuffer->WatchName(), fileName);
	}

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BufferContext::BufferUploader::RegisterTextureBuffer(DirectX::ScratchImage& image_,const BufferUniqueID id_)
{
	TemporaryTextureBufferInfoStorage temporaryTextureBufferInfoStorage;
	std::vector<D3D12_SUBRESOURCE_DATA> subResources;

	//scratchImageからサブリソースを作成
	prepareUploadCommand(image_, subResources);

	//バッファIDからバッファのポインタを取得
	auto[dstBuffer, dstResource] =  PickBufferAndResource(id_);

	//中間リソースのサイズを求める
	UINT64 const intermediateSize = GetRequiredIntermediateSize(dstResource, 0, UINT(subResources.size()));

	//サイズから中間リソースを作成する
	temporaryTextureBufferInfoStorage.intermediateResource = CreateInterMediateResource(UINT(intermediateSize));
	temporaryTextureBufferInfoStorage.id = id_;
	temporaryTextureBufferInfoStorage.subResources = subResources;


	temporaryTextureBufferInfoStorageContainer.emplace_back(temporaryTextureBufferInfoStorage);
}


template
void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_COPY_DEST>(GPUBufferBehavior* dstBuffer_);
template
void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE>(GPUBufferBehavior* dstBuffer_);
template
void BufferContext::BufferUploader::ExtractBarrier<D3D12_RESOURCE_STATE_GENERIC_READ>(GPUBufferBehavior* dstBuffer_);
